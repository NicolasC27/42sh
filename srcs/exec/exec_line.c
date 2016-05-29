/*
** exec_line.c for exec_line in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue Jan 19 00:28:24 2016 Paul Wery
** Last update Sun May 29 02:05:19 2016 Paul Wery
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	my_strlen(char *str)
{
  int	n;

  n = 0;
  while (str[n] != '\0')
    n += 1;
  return (n);
}

int	comp_words(char *word1, char *word2)
{
  int	n;

  n = 0;
  if (word1 == NULL)
    return (0);
  while (word1[n] != '\0' && word2[n] != '\0' && word1[n] == word2[n])
    n += 1;
  if (n == my_strlen(word2))
    return (1);
  return (0);
}

int	find_path(char **env)
{
  int	n;
  int	ret;

  n = 0;
  ret = 0;
  while (env[n] != NULL && ret == 0)
    {
      ret = comp_words(env[n], "PATH=");
      if (ret == 0)
	n += 1;
    }
  return (n);
}

int	find_exec(char *exec, char **opts, t_env *ev, int ret)
{
  char	*path;
  int	n;
  int	i;

  i = 1;
  n = find_path(ev->env);
  while (i <= nb_path(n, ev->env) && ret == -1)
    {
      if ((path = get_path(n, i, ev->env, 0)) == NULL
	  || (path = final_path(path, exec)) == NULL)
	return (-1);
      ret = access(path, F_OK);
      if (ret == -1)
	free(path);
      i += 1;
    }
  if (nb_path(n, ev->env) == 0 && (path = build_path("./", exec)) == NULL)
    return (-1);
  if (ret != -1 || (nb_path(n, ev->env) == 0 && access(path, F_OK) != -1))
    execve((const char*)path, opts, ev->env);
  else if (ret == -1 && access(exec, F_OK) != -1)
    execve((const char*)exec, opts, ev->env);
  else
    aff_error(exec);
  return (0);
}

char	**exec_line(char *exec, char **opts, t_env *ev, pid_t my_pid)
{
  int	status;

  if ((ev->env = set_env(exec, opts, ev->env)) == NULL ||
      (ev->env = unset_env(exec, opts, ev->env, 1)) == NULL ||
      (ev->env = swap_env(exec, opts, ev)) == NULL)
    return (NULL);
  if ((my_pid = fork()) == 0)
    {
      if (update_std(ev, 1) == -1)
	return (NULL);
      if (my_env(ev->env, opts, exec) == 0 && my_builtins(exec) == 0)
	{
	  if (where_exec(exec) == 1)
	    path_exec(exec, opts, ev->env);
	  if (where_exec(exec) == 0 && find_exec(exec, opts, ev, -1) == -1)
	    return (NULL);
	}
    }
  if (my_pid == 0)
    return (NULL);
  wait(&status);
  if (update_std(ev, 2) == -1)
    return (NULL);
  get_status(status, ev);
  return (ev->env);
}

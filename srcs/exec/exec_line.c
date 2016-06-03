/*
** exec_line.c for exec_line in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue Jan 19 00:28:24 2016 Paul Wery
** Last update Fri Jun  3 23:12:45 2016 Paul Wery
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

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

int	find_exec_next(char *exec, char **opts, t_env *ev)
{
  int	n;

  n = 0;
  while (exec[n] != '\0' && exec[n] != '/')
    n += 1;
  if (exec[n] == '/' && access(exec, F_OK) != -1)
    {
      if (execve((const char*)exec, opts, ev->env) == -1)
	aff_error(exec);
    }
  else
    aff_error(exec);
  return (0);
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
      if ((ret = access(path, F_OK)) == -1)
	free(path);
      i += 1;
    }
  if (nb_path(n, ev->env) == 0 && (path = build_path("./", exec)) == NULL)
    return (-1);
  if (ret != -1 || (nb_path(n, ev->env) == 0 && access(path, F_OK) != -1))
    {
      if (execve((const char*)path, opts, ev->env) == -1)
	aff_error(exec);
    }
  else
    if (find_exec_next(exec, opts, ev) == -1)
      return (-1);
  return (0);
}

char	**exec_line(char **opts, t_env *ev, pid_t my_pid, int status)
{
  my_exit(ev, opts);
  if ((ev->env = set_env(opts[0], opts, ev)) == NULL ||
      (ev->env = unset_env(opts[0], opts, ev->env, 1)) == NULL ||
      (ev->env = swap_env(opts[0], opts, ev)) == NULL)
    return (NULL);
  if ((my_pid = fork()) == 0)
    {
      if (update_std(ev, 1) == -1)
	return (NULL);
      if (my_env(ev, opts, opts[0]) == 0 && my_builtins(opts[0]) == 0)
	{
	  if (where_exec(opts[0]) == 1)
	    path_exec(opts[0], opts, ev->env);
	  if (where_exec(opts[0]) == 0 && find_exec(opts[0], opts, ev, -1) == -1)
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

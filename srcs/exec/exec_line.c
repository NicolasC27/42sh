/*
** exec_line.c for exec_line in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue Jan 19 00:28:24 2016 Paul Wery
** Last update Sat May 28 23:40:25 2016 Paul Wery
*/

#include <signal.h>
#include <sys/types.h>
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

int	find_exec(char *exec, char **opts, char **env, int ret)
{
  char	*path;
  int	n;
  int	i;

  i = 1;
  n = find_path(env);
  while (i <= nb_path(n, env) && ret == -1)
    {
      if ((path = get_path(n, i, env, 0)) == NULL
	  || (path = final_path(path, exec)) == NULL)
	return (-1);
      ret = access(path, F_OK);
      if (ret == -1)
	free(path);
      i += 1;
    }
  if (nb_path(n, env) == 0 && (path = build_path("./", exec)) == NULL)
    return (-1);
  if (ret == -1 && nb_path(n, env) == 0)
    ret = access(path, F_OK);
  if (ret != -1)
    execve((const char*)path, opts, env);
  else
    my_put_error("command-not-found\n");
  return (0);
}

char	**exec_line(char *exec, char **opts, t_env *ev, pid_t my_pid)
{
  int	status;

  status = my_builtins(exec, opts, ev->env);
  if ((ev->env = set_env(exec, opts, ev->env)) == NULL ||
      (ev->env = unset_env(exec, opts, ev->env, 1)) == NULL ||
      (ev->env = swap_env(exec, opts, ev)) == NULL)
    return (NULL);
  if (comp_builtins(exec, "unsetenv") == 0 && status == 0 &&
      comp_builtins(exec, "setenv") == 0 && (my_pid = fork()) == 0)
    {
      if (where_exec(exec) == 1)
	path_exec(exec, opts, ev->env);
      if (where_exec(exec) == 0
	  && (update_std(ev, 1) == -1 || find_exec(exec, opts, ev->env, -1)) == -1)
	return (NULL);
    }
  if (my_pid == 0)
    return (NULL);
  wait(&status);
  if (update_std(ev, 2) == -1)
    return (NULL);
  if (WTERMSIG(status) == SIGSEGV)
    my_putstr("Segmentation Fault\n");
  return (ev->env);
}

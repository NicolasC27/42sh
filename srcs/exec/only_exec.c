/*
** only_exec.c for only_exec in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 11:55:15 2016 Paul Wery
** Last update Sat Apr  2 00:45:28 2016 Paul Wery
*/

#include <unistd.h>
#include "mins.h"

void	path_exec(char *exec, char **opts, char **env)
{
  int	ret;

  ret = access(exec, F_OK);
  if (ret != -1)
    execve((const char*)exec, opts, env);
  if (ret == -1)
    my_put_error("command-not-found\n");
}

int	where_exec(char *exec)
{
  int	n;

  n = 0;
  if (exec[0] == '.')
    {
      while (exec[n] == '.' && exec[n] != '\0')
	n += 1;
      if (exec[n] == '/')
	return (1);
    }
  if (exec[0] == '/')
    return (1);
  return (0);
}

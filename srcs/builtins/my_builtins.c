/*
** my_cd.c for my_cd in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 19:57:50 2016 Paul Wery
** Last update Tue May 31 01:06:04 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	my_env(t_env *ev, char **opts, char *exec)
{
  int	n;

  n = 0;
  if (comp_builtins(exec, "env") == 1
      || comp_builtins(exec, "setenv") == 1)
    {
      if (opts[1] == NULL)
	{
	  while (ev->env[n] != NULL)
	    {
	      my_putstr(ev->env[n]);
	      my_putstr("\n");
	      n += 1;
	    }
	  return (1);
	}
    }
  else if ((n = equal_w_space("echo", exec)) != 0)
    {
      echo_built(exec, n, ev);
      return (1);
    }
  return (0);
}

int	my_builtins(char *exec)
{
  if (comp_builtins(exec, "env") == 1
      || comp_builtins(exec, "setenv") == 1
      || comp_builtins(exec, "unsetenv") == 1
      || comp_builtins(exec, "cd") == 1
      || equal_w_space("echo", exec) != 0)
    return (1);
  return (0);
}

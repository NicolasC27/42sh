/*
** my_cd.c for my_cd in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 19:57:50 2016 Paul Wery
** Last update Tue May 31 12:38:48 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <unistd.h>
#include "function.h"
#include "mins.h"

int	my_env(char **env, char **opts, char *exec)
{
  int	n;

  n = 0;
  if (comp_builtins(exec, "env") == 1
      || comp_builtins(exec, "setenv") == 1)
    {
      if (opts[1] == NULL)
	{
	  while (env[n] != NULL)
	    {
	      my_putstr(env[n]);
	      my_putstr("\n");
	      n += 1;
	    }
	  return (1);
	}
    }
  return (0);
}

int	my_builtins(char *exec)
{
  if (comp_builtins(exec, "env") == 1
      || comp_builtins(exec, "setenv")
      || comp_builtins(exec, "unsetenv") == 1
      || comp_builtins(exec, "cd") == 1)
    return (1);
  return (0);
}

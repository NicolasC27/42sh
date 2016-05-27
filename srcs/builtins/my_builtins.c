/*
** my_cd.c for my_cd in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 19:57:50 2016 Paul Wery
** Last update Sat Apr  2 00:44:42 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	my_cd(char *exec, char **opts)
{
  int	n;

  n = 0;
  if (comp_builtins(exec, "cd") == 1)
    {
      while (opts[n] != NULL)
	n += 1;
      if (n < 2)
	return (1);
      return (1);
    }
  return (0);
}

int	my_env(char **env, char **opts, char *exec)
{
  int	n;
  int	check;

  n = 0;
  check= 0;
  check = comp_builtins(exec, "env");
  if (check == 0)
    check = comp_builtins(exec, "setenv");
  if (check == 1)
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
  return (0);
}

int	my_builtins(char *exec, char **opts, char **env)
{
  int	ret;

  ret = my_env(env, opts, exec);
  if (ret == 1)
    return (1);
  ret = my_cd(exec, opts);
  if (ret == 1)
    return (1);
  return (0);
}

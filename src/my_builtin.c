/*
** my_builtin.c for my_builtin.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jan 23 20:02:07 2016 Nicolas Chevalier
** Last update Sat Apr  2 20:00:18 2016 Chevalier Nicolas
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

char		check_exit(char **command)
{
  int		i;
  int		count;

  count = -1;
  i =  -1;
  while (command[++count]);
  if (command[1] != NULL)
    while (command[1][++i] != '\0')
      {
	if ((command[1][i] >= '!' && command[1][i] < '-')
	    || (command[1][i] > '-' && command[1][i] < '0')
	    || (command[1][i] > '9' && command[1][i] <= '~'))
	  {
	    my_putstr("Error syntax\n");
	    return (1);
	  }
      }
  if (count > 2)
    {
      my_putstr("Error syntax\n");
      return (1);
    }
  return (0);
}

char		my_builtin_exit(char **command, t_env *env)
{
  t_env		*tmp;
  int		status;

  status = 0;
  if (check_exit(command))
    return (0);
  if (command[1] != NULL)
    status = my_getnbr(command[1]);
  if (env != NULL)
    {
      tmp = env->next;
      while (tmp != env)
  	{
  	  free(tmp->data);
  	  tmp = tmp->next;
  	}
      free(tmp);
    }
  my_free(command);
  my_putstr("\033[1;32mMinishell has stopped. \033[1;0m\n");
  exit(status);
  return (0);
}

char		my_builtin_setenv(char **command, t_env *env)
{
  int		i;

  i = -1;
  while (command[++i]);
  if (i > 3)
    my_putstr("setenv: Too many arguments\n");
  else if (command[1] != NULL)
    {
      remove_env(env, command[1]);
      env = add_env(env, command[2], command[1]);
    }
  else
    my_builtin_env(command, env);
  return (0);
}

char		my_builtin_unsetenv(char **command, t_env *env)
{
  int		i;

  i = 1;
  if (command[i] != NULL)
    while (command[i] != NULL)
      remove_env(env, command[i++]);
  else
    my_putstr("unsetenv: Too few arguments.\n");
  return (0);
}

char		my_builtin_env(char **command, t_env *env)
{
  if (command[1] != NULL)
    my_putstr("env : Too many arguments\n");
  else if (env != NULL)
    display_env(env);
  return (0);
}

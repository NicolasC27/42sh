/*
** check_command.c for check_command.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Mar 26 00:05:33 2016 Chevalier Nicolas
** Last update Tue Apr 12 23:00:26 2016 Chevalier Nicolas
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "my.h"

char		*pathornotpath(char *path)
{
  if (path == NULL)
    return ("/bin:/sbin:/usr/bin:/usr/sbin");
  return (path);
}

int		my_builtin(t_command *command, t_env *env)
{
  char		(*redirection[5])(char **, t_env *);
  char		**builtin;
  int		i;

  if ((builtin = malloc(sizeof(char *) * 5)) == NULL)
    my_puterror("Problem with a memory allocation(5)");
  builtin[0] = "exit";
  builtin[1] = "cd";
  builtin[2] = "env";
  builtin[3] = "unsetenv";
  builtin[4] = "setenv";
  redirection[0] = my_builtin_exit;
  redirection[1] = my_builtin_cd;
  redirection[2] = my_builtin_env;
  redirection[3] = my_builtin_unsetenv;
  redirection[4] = my_builtin_setenv;
  i = -1;
  while (++i < 5 && !my_strcmp(command->data[0], builtin[i], 0));
  free(builtin);
  return ((i == 5) ? (42) : redirection[i](command->data, env));
}

char		check_command(t_command *command, t_env *env)
{
  if (command->data[0] == NULL || command->data == NULL)
    return (0);
  return ((my_builtin(command, env) == 42) ? (42) : (0));
}

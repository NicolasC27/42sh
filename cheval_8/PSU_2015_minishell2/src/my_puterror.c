/*
** my_puterror.c for my_puterror.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Jan 21 02:57:36 2016 Nicolas Chevalier
** Last update Sun Jan 24 23:29:08 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include "my.h"

void		my_puterror(char *str)
{
  my_putstr_err(str);
  exit(EXIT_FAILURE);
}

char		my_puterrorcd(char *str, char *cd)
{
  my_putstr_err(cd);
  my_putstr_err(":");
  my_putstr_err(" ");
  my_putstr_err(str);
  my_putstr_err("\n");
  return (0);
}

char		my_puterror_execve(char *error, char **command)
{
  my_putstr(command[0]);
  if (my_strlen(error) == 0)
    my_putstr(": Command not found.");
  else
    my_putstr(": Permission denied.");
  my_putstr("\n");
  return (0);
}

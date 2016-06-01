/*
** my_put_error.c for my_put_error in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jan 20 02:49:57 2016 Paul Wery
** Last update Wed Jun  1 03:52:26 2016 Paul Wery
*/

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	my_put_error(char *error)
{
  write(2, error, my_strlen(error));
}

void	aff_error(char *exec)
{
  my_put_error(exec);
  if (errno == EACCES)
    my_put_error(": Permission denied.\n");
  else
    my_put_error(": Command not found.\n");
  exit(1);
}

void	aff_cd_error(char *exec, t_env *ev)
{
  ev->val_exit = 1;
  my_put_error(exec);
  if (errno == ENOENT)
    my_put_error(": No such file or directory.\n");
  else if (errno == ENOTDIR)
    my_put_error(": Not a directory.\n");
  else
    my_put_error(": Permission denied.\n");
}

void	aff_input_error(char *exec, t_env *ev)
{
  ev->val_exit = 1;
  my_put_error(exec);
  my_put_error(": No such file or directory.\n");
}

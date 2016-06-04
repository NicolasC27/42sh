/*
** my_put_error.c for my_put_error in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jan 20 02:49:57 2016 Paul Wery
<<<<<<< HEAD
** Last update Fri Jun  3 23:29:44 2016 Nicolas Chevalier
=======
** Last update Sat Jun  4 03:08:35 2016 Paul Wery
>>>>>>> master
*/

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "function.h"
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
  else if (errno == ENOEXEC)
    my_put_error(": Exec format error. Binary file not executable.\n");
  else if (errno == ENAMETOOLONG)
    my_put_error(": File name too long.\n");
  else
    my_put_error(": Command not found.\n");
  exit(1);
}

void	aff_cd_error(char *exec, t_env *ev)
{
  ev->val_exit = 1;
  my_put_error(exec);
  if (errno == EACCES)
    my_put_error(": Permission denied.\n");
  else if (errno == ENOENT)
    my_put_error(": No such file or directory.\n");
  else if (errno == ENOTDIR)
    my_put_error(": Not a directory.\n");
  else if (errno == ENAMETOOLONG)
    my_put_error(": Path name too long.\n");
  else
    my_put_error(": Permission denied.\n");
}

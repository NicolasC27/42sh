/*
** my_put_error.c for my_put_error in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jan 20 02:49:57 2016 Paul Wery
** Last update Tue May 31 12:37:46 2016 Nicolas Chevalier
*/

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
  my_put_error(": Command not found.\n");
  exit(1);
}

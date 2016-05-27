/*
** my_put_error.c for my_put_error in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jan 20 02:49:57 2016 Paul Wery
** Last update Sat Apr  2 00:45:20 2016 Paul Wery
*/

#include <unistd.h>
#include "mins.h"

void	my_put_error(char *error)
{
  write(2, error, my_strlen(error));
}

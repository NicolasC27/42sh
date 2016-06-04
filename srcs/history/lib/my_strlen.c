/*
** my_strlen.c for 42sh in /home/gerard_v/Documents/42sh/srcs/lib
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "history.h"

int	my_strlen_out(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

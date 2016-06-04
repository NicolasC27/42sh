/*
** my_putstr.c for 42sh in /home/gerard_v/Documents/42sh/srcs/lib
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "history.h"

void	my_putchar_out(char c, int out)
{
  write(out, &c, 1);
}

void	my_putstr_out(char *str, int out)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i++;
  write(out, str, i);
}

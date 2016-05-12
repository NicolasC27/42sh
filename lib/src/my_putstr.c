/*
** my_putstr.c for my_putstr.c in /home/cheval_8/rendu/PSU_2015_minitalk/lib
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Feb  5 00:51:29 2016 Nicolas Chevalier
** Last update Thu Feb 18 23:32:26 2016 Chevalier Nicolas
*/

#include "lib.h"

int	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    my_putchar(str[i++]);
  return (0);
}

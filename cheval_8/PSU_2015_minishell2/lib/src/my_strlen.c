/*
** my_strlen.c for my_strlen.c in /home/cheval_8/rendu/PSU_2015_minitalk/lib
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Feb  6 16:56:38 2016 Nicolas Chevalier
** Last update Fri Feb 19 00:23:54 2016 Chevalier Nicolas
*/

#include	"lib.h"

int		my_strlen(char *str)
{
  int		i;

  i = 0;
  while (*str && str[i++]);
  return (i);
}

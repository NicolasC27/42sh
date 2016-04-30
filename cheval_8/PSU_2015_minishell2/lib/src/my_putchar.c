/*
** my_putchar.c for my_putchar.c in /home/cheval_8/rendu/PSU_2015_minitalk/server
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Feb  4 11:14:35 2016 Nicolas Chevalier
** Last update Thu Feb 18 23:32:14 2016 Chevalier Nicolas
*/

#include	"lib.h"

void		my_putchar(char c)
{
  write(1, &c, 1);
}

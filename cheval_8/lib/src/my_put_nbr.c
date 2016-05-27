/*
** my_put_nbr.c for my_put_nbr.c in /home/cheval_8/rendu/PSU_2015_minitalk/server
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Feb  4 11:10:22 2016 Nicolas Chevalier
** Last update Thu Feb 18 23:32:38 2016 Chevalier Nicolas
*/

#include	"lib.h"

int		my_put_nbr(int nb)
{
  if (nb < 0)
    {
      nb = -nb;
      my_putchar('-');
    }
  if (nb >= 10)
    {
      my_put_nbr(nb / 10);
      my_put_nbr(nb % 10);
    }
  else
    my_putchar(nb + '0');
  return (0);
}

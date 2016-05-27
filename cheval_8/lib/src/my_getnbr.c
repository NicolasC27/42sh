/*
** my_getnbr.c for my_getnbr.c in /home/cheval_8/rendu/PSU_2015_minitalk/lib
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Feb  4 11:19:38 2016 Nicolas Chevalier
** Last update Fri Feb 19 00:27:46 2016 Chevalier Nicolas
*/

#include "lib.h"

int		my_getnext(int nbr, int i, int nega, char *str)
{
  while (str[i] >= '0' && str[i] <= '9')
    {
      nbr = (nbr * 10);
      nbr = nbr + (str[i] - '0');
      if (nbr < 0)
	if (nbr != -2147483648 || nega == 1)
	  return (0);
      i = i + 1;
    }
  return (nbr);
}

int		my_getnbr(char *str)
{
  int		nbr;
  int		i;
  int		nega;

  nbr = 0;
  i = 0;
  nega = 1;
  while (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
    {
      if (str[i] == '-')
	nega = nega * -1;
      i = i + 1;
    }
  nbr = my_getnext(nbr, i, nega, str);
  return (nbr * nega);
}

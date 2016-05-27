/*
** my_write.c for my_write in /home/cheval_8/rendu/PSU_2015_minitalk/lib
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Feb  6 20:11:02 2016 Nicolas Chevalier
** Last update Fri Feb 19 03:07:51 2016 Chevalier Nicolas
*/

#include "lib.h"

/*
** Write a string with a color
** return -1 if failed
*/
int		my_write(char *str, char *color)
{
  if (color)
    write(1, color, my_strlen(color));
  if (!(write(1, str, my_strlen(str))))
    return (-1);
  if (color)
    write (1, DEFAULT, my_strlen(DEFAULT));
  return (0);
}

/*
** Write a number with a color
*/
int		my_write_nb(int nb, char *color)
{
  if (color)
    write(1, color, my_strlen(color));
  my_put_nbr(nb);
  if (color)
    write (1, DEFAULT, my_strlen(DEFAULT));
  return (0);
}

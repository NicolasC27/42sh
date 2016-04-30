/*
** concat.c for concat.c in /home/cheval_8/rendu/PSU_2015_tetris/lib/src
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Feb 26 17:23:32 2016 Chevalier Nicolas
** Last update Tue Apr 12 18:27:41 2016 Chevalier Nicolas
*/

#include "lib.h"

char		*concat(char *str, char *str2)
{
  char		*tmp;
  int		i;
  int		len;
  int		y;

  if ((tmp = malloc(sizeof(char) * (my_strlen(str) +
				      my_strlen(str2)))) == NULL)
    return (NULL);
  len = my_strlen(str);
  i = -1;
  while (++i < len)
    tmp[i] = str[i];
  len = my_strlen(str2);
  i -= 1;
  y = -1;
  while (++y < len)
    tmp[i++] = str2[y];
  tmp[i] = '\0';
  return (tmp);
}

/*
** my_strncmp.c for my_strncmp.c in /home/cheval_8/rendu/PSU_2015_tetris/lib/src
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Mar  8 15:18:51 2016 Chevalier Nicolas
** Last update Sat Apr  9 19:04:49 2016 Chevalier Nicolas
*/

#include	"lib.h"

char		my_strncmp(char *s1, char *s2, int len)
{
  int		i;

  i = -1;
  while ((s1[i] != '\0') && (i < len))
    {
      if (s1[i] != s2[i])
	return (0);
      i += 1;
    }
  return (1);
}

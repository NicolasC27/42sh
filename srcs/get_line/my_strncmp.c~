/*
** my_strncmp.c for my_strncmp.c in /home/cheval_8/rendu/PSU_2015_tetris/lib/src
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Mar  8 15:18:51 2016 Chevalier Nicolas
** Last update Tue Apr 19 23:48:13 2016 Chevalier Nicolas
*/

#include	"lib.h"

char		my_strncmp(char *s1, char *s2, int len)
{
  int		i;

  i = -1;
  while (s1[++i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]);
  if (len == 1)
    return (s1[i] == '=' && s2[i] == '\0');
  return ((s1[i] == s2[i] || s1[i] == ' ' || s1[i] == '\t') && s2[i] == '\0');
}

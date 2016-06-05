/*
** my_strncmp.c for my_strncmp in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Jun  2 18:14:14 2016 Nicolas Chevalier
** Last update Thu Jun  2 18:14:22 2016 Nicolas Chevalier
*/

#include	"get_line.h"

char		my_strncmp(char *s1, char *s2, int len)
{
  int		i;

  i = -1;
  while (s1[++i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]);
  if (len == 1)
    return (s1[i] == '=' && s2[i] == '\0');
  return ((s1[i] == s2[i] || s1[i] == ' ' || s1[i] == '\t') && s2[i] == '\0');
}

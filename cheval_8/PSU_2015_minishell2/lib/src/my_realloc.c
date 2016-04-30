/*
** my_realloc.c for my_realloc.c in /home/cheval_8/test/CPE_2015_Allum1/lib
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Feb 20 23:03:39 2016 Chevalier Nicolas
** Last update Sat Feb 20 23:19:16 2016 Chevalier Nicolas
*/

#include	"lib.h"

char		*my_realloc(char *old, int size)
{
  char		*new;
  int		i;

  i = -1;
  if ((new = malloc(sizeof(*new) * (my_strlen(old) + size))) == NULL)
    return (NULL);
  while (old[++i])
    new[i] = old[i];
  free(old);
  return (new);
}

/*
** my_memset.c for my_memset.c in /home/cheval_8/test/CPE_2015_Allum1/lib
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Feb 20 23:29:55 2016 Chevalier Nicolas
** Last update Sat Feb 20 23:41:44 2016 Chevalier Nicolas
*/

#include	"lib.h"

void		*my_memset(void *s, int c, int n)
{
  int		i;

  i = -1;
  while (++i < n)
    ((char *)s)[i] = c;
  return (s);
}

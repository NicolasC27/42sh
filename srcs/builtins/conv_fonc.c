/*
** conv_fonc.c for conv_fonc in /home/wery_p/rendu/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri Apr  8 20:57:17 2016 Paul Wery
** Last update Tue May 31 12:42:07 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <unistd.h>
#include "function.h"
#include "mins.h"

void	my_putstr(char *str)
{
  int	n;

  n = 0;
  while (str[n] != '\0')
    n += 1;
  write(1, str, n);
}

char	*conv_str(char *str)
{
  char	*elem;
  int	n;

  n = 0;
  if ((elem = malloc(my_strlen(str) + 1)) == NULL)
    return (NULL);
  while (str[n] != '\0')
    {
      elem[n] = str[n];
      n += 1;
    }
  elem[n] = '\0';
  return (elem);
}

char	*conv_strs(char *one, char *two, char *three)
{
  char	*elem;
  int	n;
  int	i;

  n = 0;
  if ((elem = malloc(my_strlen(one) + my_strlen(two)
                     + my_strlen(three) + 1)) == NULL)
    return (NULL);
  i = 0;
  while (one[i] != '\0')
    elem[n++] = one[i++];
  i = 0;
  while (two[i] != '\0')
    elem[n++] = two[i++];
  i = 0;
  while (three[i] != '\0')
    elem[n++] = three[i++];
  elem[n] = '\0';
  return (elem);
}

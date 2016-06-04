/*
** valid_line.c for valid_line in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Mar 16 01:34:12 2016 Paul Wery
** Last update Sat Jun  4 16:04:42 2016 Nicolas Chevalier
*/

#include <signal.h>
#include "mins.h"

int	valid_line(char *str)
{
  int	n;

  n = 0;
  while (str[n])
    {
      if (str[n] < 32 || str[n] > 126)
	return (-1);
      n += 1;
    }
  n = 0;
  while ((str[n] == ' ' || str[n] == '\t') && str[n] != '\0')
      n += 1;
  if (str[n] == '\0')
    return (-1);
  return (0);
}

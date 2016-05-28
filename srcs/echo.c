/*
** echo.c for echo in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri May 27 15:30:57 2016 Paul Wery
** Last update Fri May 27 15:52:09 2016 Paul Wery
*/

#include "mins.h"

static void	afferror(int state)
{
  if (state < 0)
    {
      if (state == -1)
	my_put_error("Unmatched \".\n");
      else
	my_put_error("Unmatched '.\n");
    }
}

static int	pair(char *buffer, int n, int save_n, int nb_elem)
{
  while (buffer[n] != '\0')
    if (buffer[n++] == '"')
      nb_elem += 1;
  if ((nb_elem % 2) == 1)
    {
      afferror(-1);
      return (-1);
    }
  n = save_n;
  while (buffer[n] != '\0')
    if (buffer[n++] == '\'')
      nb_elem += 1;
  if ((nb_elem % 2) == 1)
    {
      afferror(-2);
      return (-1);
    }
  return (0);
}

int	echo_built(char *buffer, int n)
{
  if (pair(buffer, n, n, 0) == -1)
    return (-1);
  return (0);
}

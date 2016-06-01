/*
** pair.c for pair in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue May 31 18:27:11 2016 Paul Wery
** Last update Tue May 31 18:40:58 2016 Paul Wery
*/

#include "mins.h"

static void    afferror(int state)
{
  if (state < 0)
    {
      if (state == -1)
        my_put_error("Unmatched \".\n");
      else if (state == -2)
        my_put_error("Unmatched '.\n");
      else if (state == -3)
        my_put_error("Unmatched `.\n");
    }
}

int	pair(char *buffer, int n, int s_one, int s_two)
{
  int	magic;

  magic = 0;
  while (buffer[n] != '\0')
    {
      if ((s_two % 2) == 0 && buffer[n] == '"')
	s_one += 1;
      if ((s_one % 2) == 0 && buffer[n] == '\'')
        s_two += 1;
      if (buffer[n] == '`')
	magic += 1;
      n += 1;
    }
  if ((s_one % 2) == 1 || (s_two % 2) == 1 || (magic % 2) == 1)
    {
      if ((s_one % 2) == 1)
        afferror(-1);
      else if ((s_two % 2) == 1)
        afferror(-2);
      else if ((magic % 2) == 1)
        afferror(-3);
      return (-1);
    }
  return (0);
}

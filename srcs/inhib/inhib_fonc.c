/*
** inhib_fonc.c for inhib_fonc in /home/wery_p/rendu/PSU_2015_42sh/srcs/inhib
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue May 31 17:05:53 2016 Paul Wery
** Last update Tue May 31 18:10:45 2016 Paul Wery
*/
#include <stdio.h>
int		inhib(char *buffer, int n, int state)
{
  static int	s_one = 0;
  static int	s_two = 0;

  if (state == 1)
    {
      s_one = 0;
      s_two = 0;
      return (0);
    }
  if ((s_two % 2) == 0 && buffer[n] == '"')
    s_one += 1;
  if ((s_one % 2) == 0 && buffer[n] == '\'')
    s_two += 1;
  if ((s_one % 2) == 1 || (s_two % 2) == 1)
    return (1);
  return (0);
}

int		not_inhib(char *buffer, int n, int state)
{
  static int	s_one = 0;
  static int	s_two = 0;

  if (state == 1)
    {
      s_one = 0;
      s_two = 0;
      return (0);
    }
  if (state == 0)
    {
      if ((s_two % 2) == 0 && buffer[n] == '"')
	s_one += 1;
      if ((s_one % 2) == 0 && buffer[n] == '\'')
	s_two += 1;
    }
  if ((s_one % 2) == 1)
    return (1);
  else if ((s_two % 2) == 1)
    return (2);
  return (0);
}

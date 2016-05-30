/*
** echo_next.c for echo_next in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Mon May 30 21:31:09 2016 Paul Wery
** Last update Tue May 31 00:00:00 2016 Paul Wery
*/

#include <unistd.h>
#include "mins.h"

int	aff_char(char *echo, int s_one, int s_two, int n)
{
  if ((s_one % 2) == 1 || (s_two % 2) == 1)
    {
      if (echo[n] == '\\' && echo[n + 1] == 'n'
	  && write(1, "\n", 1) == -1)
	return (-1);
      if ((n - 1) > 0 && echo[n - 1] != '\\' && echo[n] != '\\'
	  && write(1, &echo[n], 1) == -1)
	return (-1);
    }
  else if (echo[n] != ' ' && echo[n] != '\t' && echo[n] != '\\')
    {
      if ((n - 1) > 0 && (echo[n - 1] == ' ' || echo[n -1] == '\t')
	  && write(1, " ", 1) == -1)
	return (-1);
      if (write(1, &echo[n], 1) == -1)
	return (-1);
    }
  return (0);
}

int	new_n(int new_line, char *echo)
{
  int	n;

  n = 0;
  if (new_line == 1)
    {
      while (echo[n] != '\0' && (echo[n] == ' ' || echo[n] == '\t'))
	echo[n++] = '\0';
      while (echo[n] != '\0' && echo[n] != ' ' && echo[n] != '\t')
	echo[n++] = '\0';
      while (echo[n] != '\0' && (echo[n] == ' ' || echo[n] == '\t'))
	echo[n++] = '\0';
    }
  return (n);
}

void	aff_echo(char *echo, int new_line, int s_one, int s_two)
{
  int	state;
  int	n;

  n = new_n(new_line, echo);
  while (echo[n] != '\0')
    {
      state = 0;
      if ((s_two % 2) == 0 && echo[n] == '"')
	{
	  s_one += 1;
	  state = 1;
	}
      if ((s_one % 2) == 0 && echo[n] == '\'')
	{
	  s_two += 1;
	  state = 1;
	}
      if (state == 0 && aff_char(echo, s_one, s_two, n) == -1)
	return ;
      n += 1;
    }
  if (new_line == 0)
    my_putstr("\n");
}

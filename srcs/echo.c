/*
** echo.c for echo in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri May 27 15:30:57 2016 Paul Wery
** Last update Tue May 31 00:15:10 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
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

static int	pair(char *buffer, int n, int s_one, int s_two)
{
  while (buffer[n] != '\0')
    {
      if ((s_two % 2) == 0 && buffer[n] == '"')
	s_one += 1;
      if ((s_one % 2) == 0 && buffer[n] == '\'')
	s_two += 1;
      n += 1;
    }
  if ((s_one % 2) == 1 || (s_two % 2) == 1)
    {
      afferror(-1);
      return (-1);
    }
  return (0);
}

static int	full_echo(char *echo, char *buffer, int n)
{
  int		i;

  i = 0;
  while (buffer[n] != '\0')
    echo[i++] = buffer[n++];
  echo[i] = '\0';
  return (0);
}

static int	check_opts(char *opt, char *ref)
{
  int		n;

  n = 0;
  while (opt[n] == ref[n] && opt[n] != '\0' && ref[n] != '\0')
    n += 1;
  if ((opt[n] == ' ' || opt[n] == '\t' || opt[n] == '\0')
      && ref[n] == '\0')
    return (1);
  return (0);
}

int	echo_built(char *buffer, int n)
{
  char	**opts;
  char	*echo;

  if (pair(buffer, n, 0, 0) == -1
      || (echo = malloc(my_strlen(buffer) - n + 1)) == NULL
      || full_echo(echo, buffer, n) == -1
      || (opts = get_opts(echo, 0, 0)) == NULL)
    return (-1);
  aff_echo(echo, check_opts(opts[0], "-n"), 0, 0);
  free(echo);
  free_opts(opts);
  return (0);
}

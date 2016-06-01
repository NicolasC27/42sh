/*
** echo.c for echo in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri May 27 15:30:57 2016 Paul Wery
** Last update Wed Jun  1 23:46:30 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

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
  if (opt == NULL)
    return (0);
  while (opt[n] == ref[n] && opt[n] != '\0' && ref[n] != '\0')
    n += 1;
  if ((opt[n] == ' ' || opt[n] == '\t' || opt[n] == '\0')
      && ref[n] == '\0')
    return (1);
  return (0);
}

int	echo_built(char *buffer, int n, t_env *ev)
{
  char	**opts;
  char	*echo;

  if (pair(buffer, n, 0, 0) == -1)
    {
      ev->val_exit = 1;
      return (-1);
    }
  if ((echo = malloc(my_strlen(buffer) - n + 1)) == NULL
      || full_echo(echo, buffer, n) == -1
      || (opts = get_opts(echo, 0, 0)) == NULL)
    return (-1);
  aff_echo(echo, check_opts(opts[0], "-n"), 0, 0);
  free(echo);
  free_opts(opts);
  return (0);
}

/*
** change_std_next.c for change_std_next in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jun  2 23:26:31 2016 Paul Wery
** Last update Fri Jun  3 03:28:30 2016 Paul Wery
*/

#include <unistd.h>
#include "mins.h"

int	default_io(int stdin, int stdout, int state)
{
  if (state == 1 || state == 3)
    {
      close(0);
      if (dup(stdin) == -1)
        return (-1);
    }
  if (state == 1 || state == 3)
    {
      close(1);
      if (dup(stdout) == -1)
	return (-1);
    }
  return (0);
}

int	update_std(t_env *ev, int state)
{
  if (state == 1 && ev->state_p == 1
      && (close(ev->pipe_t[0]) == -1
          || dup2(ev->pipe_t[1], 1) == -1))
    return (-1);
  if (state == 2 && ev->state_p == 1
      && (close(ev->pipe_t[1]) == -1
          || dup2(ev->pipe_t[0], 0) == -1))
    return (-1);
  return (0);
}

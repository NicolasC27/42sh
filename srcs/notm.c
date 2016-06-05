/*
** notm.c for ntom in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri Jun  3 20:52:35 2016 Paul Wery
** Last update Sun Jun  5 01:42:53 2016 Paul Wery
*/

#include <unistd.h>
#include "mins.h"

int	notm_next(t_exec *it, t_env *ev, int n)
{
  char	c[2];
  int	i;

  i = 0;
  c[1] = '\0';
  if (it->tab[n] == NULL)
    return (0);
  while (it->tab[n][i] != '$')
    i += 1;
  i += 1;
  while (it->tab[n][i] != '\0' && it->tab[n][i] != ' '
         && it->tab[n][i] != '\t')
    {
      c[0] = it->tab[n][i++];
      my_put_error(c);
    }
  my_put_error(": Undefined variable.\n");
  ev->val_exit = 1;
  return (1);
}

int	notm_sec(t_exec *it, t_env *ev)
{
  int	state;
  int	n;
  int	i;

  n = 0;
  i = 0;
  state = 0;
  if (it->error == -2)
    {
      while (it->tab[n] != NULL && state == 0)
        {
          i = 0;
          while (it->tab[n][i] != '\0' && it->tab[n][i] != '$')
            i += 1;
	  if (it->tab[n][i] == '$')
	    state = 1;
          if (it->tab[n][i] == '\0')
            n += 1;
        }
      if (notm_next(it, ev, n) == 1)
        return (1);
    }
  return (0);
}

int	notm(t_exec *it, t_env *ev)
{
  if (it->error < 0 && it->error != -2)
    {
      if (equal_w_space("echo", it->tab[0]) == 0)
	my_put_error(it->tab[0]);
      else
	my_put_error("echo");
      my_put_error(": No match.\n");
      ev->val_exit = 1;
      return (1);
    }
  else if (notm_sec(it, ev) == 1)
    return (1);
  return (0);
}

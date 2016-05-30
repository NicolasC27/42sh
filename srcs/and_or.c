/*
** and_or.c for and_or in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue May 31 00:17:47 2016 Paul Wery
** Last update Tue May 31 00:21:20 2016 Paul Wery
*/

#include "mins.h"

int	and_or(t_env *ev, t_exec *it)
{
  int	num;

  num = elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if ((num == 3 && ev->val_exit == 0)
      || (num == 4 && ev->val_exit) == 1)
    return (1);
  return (0);
}

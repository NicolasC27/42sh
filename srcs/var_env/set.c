/*
** set.c for set in /home/wery_p/rendu/PSU_2015_42sh/srcs/var_env
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sun Jun  5 04:19:23 2016 Paul Wery
** Last update Sun Jun  5 09:45:16 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	add_set(t_var *list_v, char *elem, char *var, int ret)
{
  t_var	*it;
  int	n;

  it = list_v->next;
  while (it != list_v)
    {
      n = 0;
      while (it->name[n] != '\0' && elem[n] != '\0' &&it->name[n] == elem[n])
	n += 1;
      if (it->name[n] == '\0' && elem[n] == '\0')
	{
	  free(elem);
	  if (it->value != NULL)
	    free(it->value);
	  it->value = var;
	  return (ret);
	}
      it = it->next;
    }
  if (add_var_prev(list_v, elem, var) == -1)
    return (-1);
  return (ret);
}

int	set_next(t_set *s, t_env *ev, char **opts)
{
  if (opts[s->n + 1] != NULL && opts[s->n + 2] != NULL)
    {
      if ((s->var = added_value(opts[s->n + 2])) == NULL
	  || add_set(ev->free.list_v, s->elem, s->var, 0) == -1)
	return (-1);
      s->n += 2;
    }
  else if (add_set(ev->free.list_v, s->elem, NULL, 0) == -1)
    return (-1);
  return (0);
}

void	varerror(t_env *ev, char *elem)
{
  free(elem);
  my_put_error("set: Variable name must begin with a letter.\n");
  ev->val_exit = 1;
}

int	set(t_env *ev, char **opts)
{
  t_set	s;

  s.n = 1;
  while (opts[s.n] != NULL)
    {
      if ((s.elem = added_elem(opts[s.n])) == NULL)
	return (-1);
      if ((s.elem[0] > 64 && s.elem[0] < 91)
	  || (s.elem[0] > 96 && s.elem[0] < 123))
	{
	  if (my_strlen(s.elem) == my_strlen(opts[s.n]))
	    {
	      if (set_next(&s, ev, opts) == -1)
		return (-1);
	    }
	  else if (set_same(ev, &s, opts) == -1)
	    return (-1);
	}
      else
	varerror(ev, s.elem);
      if (opts[s.n] != NULL)
	s.n += 1;
    }
  return (0);
}

int	set_unset_var(t_var *list_v, char **opts, t_env *ev)
{
  if (opts[1] != NULL)
    {
      if (comp_builtins(opts[0], "set") == 1
	  && set(ev, opts) == -1)
	return (-1);
      else if (comp_builtins(opts[0], "unset") == 1)
	unset(list_v, opts);
    }
  else if (comp_builtins(opts[0], "unset") == 1)
    {
      my_put_error("unset: Too few arguments.\n");
      ev->val_exit = 1;
    }
  return (0);
}

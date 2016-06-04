/*
** order_list.c for order_list in /home/wery_p/rendu/PSU_2015_42sh/srcs/global
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jun  4 21:25:32 2016 Paul Wery
** Last update Sat Jun  4 22:10:25 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	empty_order(t_order *root)
{
  t_order	*it;
  t_order	*save;

  it = root->next;
  while (it != root)
    {
      save = it->next;
      free(it->name);
      free(it);
      it = save;
    }
}

void	delete_order(t_order **root)
{
  empty_order(*root);
  free(*root);
  *root = NULL;
}

int		add_order_prev(t_order *elem, char *name)
{
  t_order	*new_elem;

  if ((new_elem = malloc(sizeof(*new_elem))) == NULL)
    return (-1);
  new_elem->name = name;
  new_elem->next = elem;
  new_elem->prev = elem->prev;
  elem->prev->next = new_elem;
  elem->prev = new_elem;
  return (0);
}

t_order		*create_order(void)
{
  t_order	*root;

  if ((root = malloc(sizeof(*root))) == NULL)
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

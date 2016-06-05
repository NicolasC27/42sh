/*
** order_list.c for order_list in /home/wery_p/rendu/PSU_2015_42sh/srcs/global
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jun  4 21:25:32 2016 Paul Wery
** Last update Sun Jun  5 05:48:39 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	empty_var(t_var *root)
{
  t_var	*it;
  t_var	*save;

  it = root->next;
  while (it != root)
    {
      save = it->next;
      free(it->name);
      free(it->value);
      free(it);
      it = save;
    }
}

void	delete_var(t_var **root)
{
  empty_var(*root);
  free(*root);
  *root = NULL;
}

void	delete_var_elem(t_var *elem)
{
  elem->next->prev = elem->prev;
  elem->prev->next = elem->next;
  free(elem->name);
  free(elem->value);
  free(elem);
}

int	add_var_prev(t_var *elem, char *name, char *value)
{
  t_var	*new_elem;

  if ((new_elem = malloc(sizeof(*new_elem))) == NULL)
    return (-1);
  new_elem->name = name;
  new_elem->value = value;
  new_elem->next = elem;
  new_elem->prev = elem->prev;
  elem->prev->next = new_elem;
  elem->prev = new_elem;
  return (0);
}

t_var	*create_var(void)
{
  t_var	*root;

  if ((root = malloc(sizeof(*root))) == NULL)
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

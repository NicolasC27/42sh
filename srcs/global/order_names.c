/*
** order_names.c for order_names in /home/wery_p/rendu/PSU_2015_42sh/srcs/global
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jun  4 21:00:22 2016 Paul Wery
** Last update Sat Jun  4 23:21:59 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "mins.h"

int     conc(char *name, int n, char *replace)
{
  int   i;

  i = 0;
  while (name[i] != '\0')
    replace[n++] = name[i++];
  replace[n] = '\0';
  return (n);
}

void		swap_order(t_order *one, t_order *two)
{
  one->prev->next = two;
  two->next->prev = one;
  one->next = two->next;
  two->prev = one->prev;
  one->prev = two;
  two->next = one;
}

int	name_order(char *one, char *two, int onev, int twov)
{
  int	n;

  n = 0;
  while (one[n] != '\0' && two[n] != '\0')
    {
      onev = one[n];
      twov = two[n];
      if (onev > 96 && onev < 123)
	onev -= 32;
      if (twov > 96 && twov < 123)
	twov -= 32;
      if (onev > twov)
	return (1);
      else if (onev < twov)
	return (0);
      n += 1;
    }
  if (one[0] < two[0])
    return (1);
  return (0);
}

void		order_order(t_order *order)
{
  int		state;
  t_order	*it;

  state = 1;
  while (state == 1)
    {
      state = 0;
      it = order->next;
      while (it->next != order)
	{
	  if (name_order(it->name, it->next->name, 0, 0) == 1)
	    {
	      swap_order(it, it->next);
	      state = 1;
	    }
	  else
	    it = it->next;
	}
    }
}

t_order		*order_names(DIR *directory)
{
  t_order	*order;
  t_dir		*file;
  char		*name;

  if ((order = create_order()) == NULL)
    return (NULL);
  while ((file = readdir(directory)) != NULL)
    {
      if (file->d_name[0] != '.')
	{
	  if ((name = malloc(my_strlen(file->d_name) + 1)) == NULL)
	    return (NULL);
	  conc(file->d_name, 0, name);
	  if (add_order_prev(order, name) == -1)
	    return (NULL);
	}
    }
  order_order(order);
  return (order);
}

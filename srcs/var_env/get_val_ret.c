/*
** get_val_ret.c for get_val_ret in /home/wery_p/rendu/PSU_2015_42sh/srcs/var_env
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jun  4 04:51:04 2016 Paul Wery
** Last update Sun Jun  5 08:43:48 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	check_var_list(t_var *list_v, char *ref)
{
  t_var	*it;
  int	n;

  it = list_v->next;
  while (it != list_v)
    {
      n = 0;
      while (it->name[n] != '\0' && ref[n] != '\0' && it->name[n] == ref[n])
	n += 1;
      if (it->name[n] == '\0' && ref[n] == '\0')
	return (1);
      it = it->next;
    }
  return (0);
}

int	size_ret(int val)
{
  int	n;

  n = 0;
  while (val > 0)
    {
      val /= 10;
      n += 1;
    }
  if (n == 0)
    n = 1;
  return (n);
}

char	*get_var_value(t_var *list_v, char *ref, char *val_exit, int n)
{
  t_var	*it;

  it = list_v->next;
  while (it != list_v)
    {
      n = 0;
      while (it->name[n] != '\0' && ref[n] != '\0' && it->name[n] == ref[n])
	n += 1;
      if (it->name[n] == '\0' && ref[n] == '\0')
	{
	  n = 0;
	  if ((val_exit = malloc(my_strlen(it->value) + 1)) == NULL)
	    return (NULL);
	  while (it->value[n] != '\0')
	    {
	      val_exit[n] = it->value[n];
	      n += 1;
	    }
	  val_exit[n] = '\0';
	  return (val_exit);
	}
      it = it->next;
    }
  return (val_exit);
}

char	*get_val_ret(int val, char *buffer, t_env *ev, char *ext)
{
  char	*val_exit;
  int	size;

  if (check_loc(buffer, ev, ext) == 2 || check_loc(buffer, ev, ext) == 1)
    {
      if (check_loc(buffer, ev, ext) == 2)
	val = getpid();
      if ((val_exit = malloc(size_ret(val) + 1)) == NULL)
	return (NULL);
      size = size_ret(val);
      val_exit[size--] = '\0';
      while (size >= 0)
	{
	  val_exit[size] = val % 10 + 48;
	  val /= 10;
	  size -= 1;
	}
    }
  else if ((val_exit = get_var_value(ev->free.list_v, ext, NULL, 0)) == NULL)
    return (NULL);
  return (val_exit);
}

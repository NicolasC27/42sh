/*
** unset.c for unset in /home/wery_p/rendu/PSU_2015_42sh/srcs/var_env
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sun Jun  5 06:28:40 2016 Paul Wery
** Last update Sun Jun  5 06:29:48 2016 Paul Wery
*/

#include <unistd.h>
#include "mins.h"

int	unsetable(char *name, char *str, t_var *elem)
{
  int	n;

  n = 0;
  while (name[n] != '\0' && str[n] != '\0' && name[n] == str[n])
    n += 1;
  if (name[n] == '\0' && str[n] == '\0')
    {
      delete_var_elem(elem);
      return (1);
    }
  return (0);
}

void	unset(t_var *list_v, char **opts)
{
  t_var	*it;
  int	n;

  n = 1;
  it = list_v->next;
  while (opts[n] != NULL)
    {
      while (it != list_v && unsetable(it->name, opts[n], it) == 0)
	it = it->next;
      n += 1;
    }
}

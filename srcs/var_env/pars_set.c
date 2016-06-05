/*
** pars_set.c for pars_set in /home/wery_p/rendu/PSU_2015_42sh/srcs/var_env
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sun Jun  5 04:32:12 2016 Paul Wery
** Last update Sun Jun  5 09:43:11 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	aff_set(t_var *list_v)
{
  t_var	*it;

  it = list_v->next;
  while (it != list_v)
    {
      my_putstr(it->name);
      if (it->value != NULL)
	{
	  my_putstr("\t\t");
	  my_putstr(it->value);
	}
      my_putstr("\n");
      it = it->next;
    }
}

char	*added_value(char *str)
{
  char	*var;
  int	n;

  n = 0;
  if ((var = malloc(my_strlen(str) + 1)) == NULL)
    return (NULL);
  while (str[n] != '\0')
    {
      var[n] = str[n];
      n += 1;
    }
  var[n] = '\0';
  return (var);
}

char	*added_same(char *str)
{
  char	*var;
  int	n;
  int	i;

  n = 0;
  i = 0;
  if ((var = malloc(my_strlen(str) + 1)) == NULL)
    return (NULL);
  while (str[i] != '\0' && str[i] != '=')
    i += 1;
  if (str[i] != '\0')
    i += 1;
  while (str[i] != '\0')
    var[n++] = str[i++];
  while (n <= my_strlen(str))
    var[n++] = '\0';
  return (var);
}

char	*added_elem(char *str)
{
  char	*add;
  int	n;

  n = 0;
  if ((add = malloc(my_strlen(str) + 1)) == NULL)
    return (NULL);
  while (str[n] != '\0' && str[n] != '=')
    {
      add[n] = str[n];
      n += 1;
    }
  while (n <= my_strlen(str))
    add[n++] = '\0';
  return (add);
}

int	set_same(t_env *ev, t_set *s, char **opts)
{
  if ((opts[s->n] != NULL && (s->var = added_same(opts[s->n])) == NULL)
      || add_set(ev->free.list_v, s->elem, s->var, 0) == -1)
    return (-1);
  return (0);
}

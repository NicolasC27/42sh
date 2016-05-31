/*
** red_left.c for red_left in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 22:32:13 2016 Paul Wery
** Last update Tue May 31 12:36:40 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <unistd.h>
#include "function.h"
#include "mins.h"

int	equal_w_space(char *one, char *two)
{
  int	n;
  int	i;

  n = 0;
  i = 0;
  while (two[n] != '\0' && (two[n] == ' ' || two[n] == '\t'))
    n += 1;
  while (one[i] == two[n] && one[i] != '\0' && two[n] != '\0')
    {
      n += 1;
      i += 1;
    }
  if (one[i] == '\0' && (two[n] == '\0' || two[n] == ' ' || two[n] == '\t'))
    return (n);
  return (0);
}

static int	equal(char *one, char *two)
{
  int		n;

  n = 0;
  if (two == NULL)
    return (0);
  while (one[n] == two[n] && one[n] != '\0' && two[n] != '\0')
    n += 1;
  if (one[n] == '\0' && two[n] == '\0')
    return (1);
  return (0);
}

static int	loop(t_exec *elem)
{
  char		*line;

  line = NULL;
  while (equal(elem->next->tab[0], line) == 0)
    {
      if (line != NULL)
	free(line);
      my_putstr("? ");
      if ((line = get_next_line()) == NULL)
	return (-1);
    }
  if (line != NULL)
    free(line);
  return (0);
}

int		wait_lef(t_exec *list, t_exec *it, int num)
{
  t_exec	*elem;

  elem = it;
  while (elem != list && elem->tab[0][0] != ';')
    {
      num = elem_redirection(elem->tab[0], "<<,>>,||,&&,<,>,|,&,;");
      if (num == 1)
        {
          if (elem->next == list
              || elem_redirection(elem->next->tab[0],
				  "<<,>>,||,&&,<,>,|,&,;") != 0)
            {
              my_put_error("Missing name for redirect.\n");
              return (0);
            }
          else if (loop(elem) == -1)
	    return (-1);
	}
      elem = elem->next;
    }
  return (0);
}

t_exec	*jump(t_exec *list, t_exec *it)
{
  int	num;

  num = elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (num == 1 || num == 2 || num == 5 || num == 6)
    {
      if (it->next != list)
	it = it->next->next;
      else
	it = it->next;
    }
  else
    it = it->next;
  return (it);
}

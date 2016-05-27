/*
** full_list.c for full_list in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 17:57:04 2016 Paul Wery
** Last update Wed May 25 18:08:40 2016 Paul Wery
*/

#include <unistd.h>
#include "mins.h"

int	full_list(t_exec *list, char **pars)
{
  int	n;
  char	**opts;

  n = 0;
  while (pars[n] != NULL)
    {
      if ((opts = get_opts(pars[n], 0, 0)) == NULL
	  || (add_elem_prev(list, opts)) == -1)
	return (-1);
      n += 1;
    }
  return (0);
}

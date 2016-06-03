/*
** full_list.c for full_list in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 17:57:04 2016 Paul Wery
** Last update Fri Jun  3 04:47:49 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	put_echo_line(char *echo, t_exec *list, int error, int error_two)
{
  char	**opts;
  int	n;

  n = 0;
  if ((opts = malloc(2 * sizeof(char*))) == NULL)
    return (-1);
  if ((opts[0] = malloc(my_strlen(echo) + 1)) == NULL)
    return (-1);
  while (echo[n] != '\0')
    {
      opts[0][n] = echo[n];
      n += 1;
    }
  opts[0][n] = '\0';
  opts[1] = NULL;
  if (add_elem_prev(list, opts, error, error_two) == -1)
    return (-1);
  return (0);
}

int	full_list(t_exec *list, char **pars, t_env *ev)
{
  int	n;
  int	error;
  int	error_two;
  char	**opts;

  n = 0;
  while (pars[n] != NULL)
    {
      error = 0;
      error_two = 0;
      if ((pars[n] = echo_star(pars[n], &error)) == NULL
	  || (pars[n] = echo_var(pars[n], &error_two, ev->env)) == NULL)
	return (-1);
      if (equal_w_space("echo", pars[n]) == 0)
	{
	  if ((opts = get_opts(pars[n], 0, 0)) == NULL
	      || (add_elem_prev(list, opts, error, error_two)) == -1)
	    return (-1);
	}
      else if (put_echo_line(pars[n], list, error, error_two) == -1)
	return (-1);
      n += 1;
    }
  return (0);
}

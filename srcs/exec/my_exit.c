/*
** my_exit.c for my_exit in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 18:44:21 2016 Paul Wery
** Last update Sun Jun  5 05:30:25 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	valid_val(char *buffer)
{
  int	n;

  n = 0;
  if (buffer[n] == '-' && buffer[n + 1] == '\0')
    return (-1);
  if (buffer[n] == '-')
    n += 1;
  while (buffer[n] != '\0')
    {
      if (buffer[n] < 48 || buffer[n] > 57)
	return (-1);
      n += 1;
    }
  return (0);
}

int	get_val_return(char *word1, int i, int status, int sign)
{
  if (word1[i] == '-')
    {
      i = i + 1;
      sign = 1;
    }
  while (word1[i] != '\0')
    {
      status = (status * 10) + (word1[i] - 48);
      i = i + 1;
    }
  if (sign == 1)
    status = status * -1;
  return (status);
}

void	free_all(t_env *ev, int status)
{
  free(ev->free.buffer);
  free_opts(ev->free.pars);
  delete_list(&ev->free.list);
  delete_var(&ev->free.list_v);
  free_opts(ev->env);
  free(ev->oldpwd);
  exit(status);
}

void	my_exit(t_env *ev, char **opts)
{
  int	status;

  if (ev->state_p == 1)
    return ;
  if (comp_builtins(opts[0], "exit") == 0)
    return ;
  if ((opts[1] != NULL && opts[2] != NULL)
      || (opts[1] != NULL && valid_val(opts[1])) == 1)
    {
      my_put_error("exit: Expression Syntax.\n");
      ev->val_exit = 1;
    }
  if (opts[1] != NULL)
    status = get_val_return(opts[1], 0, 0, 0);
  else
    status = 0;
  free_all(ev, status);
}

/*
** command_exec.c for command_exec in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 19:22:23 2016 Paul Wery
** Last update Fri May 27 02:17:01 2016 Paul Wery
*/

#include <unistd.h>
#include "mins.h"

int	elem_redirection(char *elem, char *ref)
{
  int	n;
  int	i;
  int	num;

  i = 0;
  num = 1;
  while (ref[i] != '\0')
    {
      n = 0;
      while (elem[n] == ref[i] && elem[n] != '\0'
	     && ref[i] != '\0' && ref[i] != ',')
	{
	  n += 1;
	  i += 1;
	}
      if (elem[n] == '\0' && (ref[i] == ',' || ref[i] == '\0'))
	return (num);
      while (ref[i] != ',' && ref[i] != '\0')
	i += 1;
      if (ref[i] != '\0')
	i += 1;
      num += 1;
    }
  return (0);
}

t_exec	*next_command(t_exec *list, t_exec *it)
{
  while (it != list
	 && elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") != 9)
    it = it->next;
  return (it);
}

t_exec	*next_exec(t_exec *it, t_exec *list, t_env *ev)
{
  int	num;

  if (it == list)
    return (it);
  num = elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (num == 3 || num == 4 || num == 7 || num == 8)
    return (it->next);
  else if (num == 1 || num == 2 || num == 5 || num == 6)
    {
      if (it->next != list)
	return (it->next->next);
      else
	return (it->next);
    }
  if (default_io(ev->stdin, ev->stdout, 3) == -1)
    return (NULL);
  return (it);
}

int		use_pipe(t_exec *list, t_exec *it, t_env *ev)
{
  ev->state_p = 0;
  if (elem_redirection(it->prev->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 9
      && default_io(ev->stdin, ev->stdout, 1) == -1)
    return (-1);
  if (list == it)
    return (0);
  if (elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 7)
    {
      ev->state_p = 1;
      if (pipe(ev->pipe_t) == -1)
	return (-1);
    }
  return (0);
}

char		**exec_list(t_exec *list, t_env *ev)
{
  t_exec	*it;
  int		errin;
  int		errout;

  it = list->next;
  while (valid_command(list) == 0 && it != list)
    {
      if (open_files(list, it, 0, 0) == -1
	  || use_pipe(list, it->next, ev) == -1
	  || (errin = change_input(list, it->next, 0)) == -1
	  || (errout = change_output(list, it->next, ev->stdout, 0)) == -1)
	return (NULL);
      if (errin == -2 || errout == -2)
	it = next_command(list, it);
      else if (elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 0)
	{
	  if ((ev->env = exec_line(it->tab[0], it->tab, ev, 1)) == NULL
	      || (it != list && (it = next_exec(it->next, list, ev)) == NULL))
	    return (NULL);
	}
      else
	it = jump(list, it);
    }
  return (ev->env);
}

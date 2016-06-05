/*
** command_exec.c for command_exec in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 19:22:23 2016 Paul Wery
** Last update Sun Jun  5 03:17:08 2016 Nicolas Chevalier
*/

#include <stdio.h>
#include <unistd.h>
#include "mins.h"

int	elem_redirection(char *elem, char *ref)
{
  int	n;
  int	i;
  int	num;

  i = 0;
  num = 1;
  while (elem != NULL && ref != NULL && ref[i] != '\0')
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
  int	num;

  num = elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (num == 3 || num == 4 || num == 9)
    it = it->next;
  while (it != list
	 && elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") != 9
	 && elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") != 3
	 && elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") != 4)
    it = it->next;
  return (it);
}

t_exec	*next_exec(t_exec *it, t_exec *list, t_env *ev)
{
  int	num;

  if (ev->val_exit == 1)
    return (next_command(list, it->prev));
  if (it == list)
    return (it);
  num = elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (num == 7 || num == 8)
    return (it->next);
  else if (num == 1 || num == 2 || num == 5 || num == 6)
    {
      if (num == 1)
	remove(".my_teemo");
      if (it->next != list)
	return (it->next->next);
      else
	return (it->next);
    }
  if (default_io(ev->stdin, ev->stdout, 3) == -1)
    return (NULL);
  return (it);
}

int		use_pipe(t_exec *list, t_exec *it, t_env *ev, int num)
{
  ev->state_p = 0;
  if (elem_redirection(it->prev->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 9
      && default_io(ev->stdin, ev->stdout, 1) == -1)
    return (-1);
  if (list == it)
    return (0);
  if (list != it->next && list != it->next->next)
    num = elem_redirection(it->next->next->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 7)
    {
      ev->state_p = 1;
      if (pipe(ev->pipe_t) == -1)
	return (-1);
    }
  else if (num == 7 &&
	   (elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 2
	    || elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 5
	    || elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 6))
    {
      ev->state_p = 1;
      if (pipe(ev->pipe_t) == -1)
	return (-1);
    }
  return (0);
}

char		**exec_list(t_exec *list, t_env *ev, int in, int out)
{
  t_exec	*it;
  int		op;

  it = list->next;
  while (valid_command(list) == 0 && it != list)
    {
      if ((op = open_files(list, it, 0, ev)) == -1
	  || (op == 0 && use_pipe(list, it->next, ev, 0) == -1)
	  || (op == 0 && (in = change_input(list, it->next, 0, ev)) == -1)
	  || (op == 0 && (out = change_output(list, it->next, ev->stdout, ev)) == -1))
	return (NULL);
      if (op == -2 || in == -2 || out == -2
	  || and_or(ev, it) == 1 || notm(it, ev) == 1)
	  it = next_command(list, it);
      else if (elem_redirection(it->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 0)
	{
	  ev->val_exit = 0;
	  if ((ev->env = exec_line(it->tab, ev, 1, 0)) == NULL
	      || (it != list && (it = next_exec(it->next, list, ev)) == NULL))
	    return (NULL);
	}
      else
	it = jump(list, it);
    }
  return (ev->env);
}

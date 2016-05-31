/*
** change_std.c for change_std in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 20:44:03 2016 Paul Wery
** Last update Tue May 31 13:50:54 2016 Lucas Debouté
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "mins.h"

int	change_output(t_exec *list, t_exec *elem, int stdout, int num)
{
  if (elem != list)
    num = elem_redirection(elem->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (elem == list || num == 9)
    {
      close(1);
      if (dup(stdout) == -1)
        return (-1);
      return (1);
    }
  else if (num == 2 || num == 6)
    {
      if (elem->next == list)
        {
          my_put_error("Missing name for redirect.\n");
          return (-2);
        }
      close(1);
      if ((num == 2 && (open(elem->next->tab[0], O_APPEND | O_WRONLY)) == -1)
          || (num == 6 && ((open(elem->next->tab[0], O_WRONLY | O_TRUNC))) == -1))
        return (-1);
    }
  return (0);
}

int	change_input(t_exec *list, t_exec *elem, int num)
{
  if (elem != list)
    num = elem_redirection(elem->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (num == 5)
    {
      if (elem->next == list)
        {
          my_put_error("Missing name for redirect.\n");
          return (-2);
        }
      close(0);
      if ((num = open(elem->next->tab[0], O_RDONLY)) == -1)
        return (-1);
      if (list != elem->next && list != elem->next->next)
	{
	  num = elem_redirection(elem->next->next->tab[0],
				 "<<,>>,||,&&,<,>,|,&,;");
	  if ((num == 2 || num == 6)
	      && change_output(list, elem->next->next, 1, 0) == -1)
	    return (-1);
	}
    }
  return (0);
}

int	default_io(int stdin, int stdout, int state)
{
  if (state == 1 || state == 3)
    {
      close(0);
      if (dup(stdin) == -1)
	return (-1);
    }
  if (state == 1 || state == 3)
    {
      close(1);
      if (dup(stdout) == -1)
	return (-1);
    }
  return (0);
}

int		open_files(t_exec *list, t_exec *it, int num, int fd)
{
  t_exec	*elem;

  if (it->prev != list && it->prev->tab[0][0] != ';')
    return (0);
  elem = it;
  if (wait_lef(list, it, 0) == -1)
    return (-1);
  while (elem != list && elem->tab[0][0] != ';')
    {
      num = elem_redirection(elem->tab[0], "<<,>>,||,&&,<,>,|,&,;");
      if (elem->next != list
	  && elem_redirection(elem->next->tab[0], "<<,>>,||,&&,<,>,|,&,;") == 0)
	{
	  if (num == 2 && ((fd = open(elem->next->tab[0], O_CREAT,
				      S_IRUSR | S_IWUSR)) == -1
			   || close(fd) == -1))
	    return (-1);
	  if (num == 6 && ((fd = open(elem->next->tab[0], O_CREAT | O_TRUNC,
				      S_IRUSR | S_IWUSR)) == -1
			   || close(fd) == -1))
	    return (-1);
	}
      elem = elem->next;
    }
  return (0);
}

int	update_std(t_env *ev, int state)
{
  if (state == 1 && ev->state_p == 1
      && (close(ev->pipe_t[0]) == -1
	  || dup2(ev->pipe_t[1], 1) == -1))
    return (-1);
  if (state == 2 && ev->state_p == 1
      && (close(ev->pipe_t[1]) == -1
	  || dup2(ev->pipe_t[0], 0) == -1))
    return (-1);
  return (0);
}

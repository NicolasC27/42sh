/*
** change_std.c for change_std in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 20:44:03 2016 Paul Wery
<<<<<<< HEAD
<<<<<<< HEAD
** Last update Tue May 31 12:36:23 2016 Nicolas Chevalier
=======
** Last update Fri Jun  3 00:17:21 2016 Paul Wery
>>>>>>> master
=======
** Last update Sat Jun  4 02:55:53 2016 Paul Wery
>>>>>>> master
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "function.h"
#include "mins.h"

int	change_output_next(int num, t_exec *elem, t_env *ev, t_exec *list)
{
  if (num == 2 || num == 6)
    {
      if (elem->next == list)
        {
	  files_error(NULL, ev, 1);
          return (-2);
        }
      if (close(1) == -1)
	return (-1);
      if ((num == 2 && (open(elem->next->tab[0], O_APPEND | O_WRONLY)) == -1)
          || (num == 6 && ((open(elem->next->tab[0],
				 O_WRONLY | O_TRUNC))) == -1))
	{
	  files_error(elem->next->tab[0], ev, 0);
	  return (-2);
	}
    }
  return (0);
}

int	change_output(t_exec *list, t_exec *elem, int stdout, t_env *ev)
{
  int	num;

  num = 0;
  if (elem != list)
    num = elem_redirection(elem->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (elem == list || num == 9)
    {
      if (close(1) == -1 || dup(stdout) == -1)
	return (-1);
      return (1);
    }
  if (change_output_next(num, elem, ev, list) == -2)
    return (-2);
  return (0);
}

int	change_input_next(t_exec *list, t_exec *elem, t_env *ev)
{
  int	num;

  if ((num = open(elem->next->tab[0], O_RDONLY)) == -1)
    {
      files_error(elem->next->tab[0], ev, 0);
      return (-2);
    }
  if (list != elem->next && list != elem->next->next)
    {
      num = elem_redirection(elem->next->next->tab[0],
			     "<<,>>,||,&&,<,>,|,&,;");
      if ((num == 2 || num == 6)
	  && change_output(list, elem->next->next, 1, 0) == -1)
	{
	  files_error(elem->next->tab[0], ev, 0);
	  return (-2);
	}
    }
  return (0);
}

int	change_teemo(t_exec *list, t_exec *elem, t_env *ev)
{
  int	num;

  if ((num = open(".my_teemo", O_RDONLY)) == -1)
    {
      files_error(".my_teemo", ev, 0);
      return (-2);
    }
  if (list != elem->next && list != elem->next->next)
    {
      num = elem_redirection(elem->next->next->tab[0],
			     "<<,>>,||,&&,<,>,|,&,;");
      if ((num == 2 || num == 6)
	  && change_output(list, elem->next->next, 1, 0) == -1)
	{
	  files_error(elem->next->tab[0], ev, 0);
	  return (-2);
	}
    }
  return (0);
}

int	change_input(t_exec *list, t_exec *elem, int num, t_env *ev)
{
  if (elem != list)
    num = elem_redirection(elem->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (num == 5 || num == 1)
    {
      if (elem->next == list)
        {
	  files_error(NULL, ev, 1);
          return (-2);
        }
      if (close(0) == -1)
	return (-1);
    }
  if (num == 5 && change_input_next(list, elem, ev) == -2)
    return (-2);
  else if (num == 1 && change_teemo(list, elem, ev) == -2)
    return (-2);
  return (0);
}

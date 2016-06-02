/*
** gest_files.c for gest_files in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jun  2 20:48:47 2016 Paul Wery
** Last update Fri Jun  3 00:17:10 2016 Paul Wery
*/

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "mins.h"

void	files_error(char *file, t_env *ev, int state)
{
  ev->val_exit = 1;
  if (state == 0)
    my_put_error(file);
  if (errno == EACCES)
    my_put_error(": Permission denied.\n");
  else if (errno == EFAULT)
    my_put_error(": Points outside your accessible address space.\n");
  else if (errno == EFBIG)
    my_put_error(": File is too big.\n");
  else if (errno == EISDIR)
    my_put_error(": Is a directory.\n");
  else if (errno == ENAMETOOLONG)
    my_put_error(": File name too long.\n");
  else if (errno == ENOTDIR)
    my_put_error(": Not a directory.\n");
  else if (errno == ENOENT)
    my_put_error(": No such file or directory.\n");
  else
    my_put_error("Missing name for redirect.\n");
}

int	open_files_next(int num, t_exec *elem)
{
  int	fd;

  if (num == 2 && ((fd = open(elem->next->tab[0], O_CREAT,
			      S_IRUSR | S_IWUSR)) == -1
		   || close(fd) == -1))
    return (-2);
  if (num == 6 && ((fd = open(elem->next->tab[0], O_CREAT | O_TRUNC,
			      S_IRUSR | S_IWUSR)) == -1
		   || close(fd) == -1))
    return (-2);
  return (0);
}

int	open_files(t_exec *list, t_exec *it, int num, t_env *ev)
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
	if (open_files_next(num, elem) == -2)
	  {
	    files_error(elem->next->tab[0], ev, 0);
	    return (-2);
	  }
      elem = elem->next;
    }
  return (0);
}

/*
** red_left.c for red_left in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 22:32:13 2016 Paul Wery
<<<<<<< HEAD
** Last update Tue May 31 12:36:40 2016 Nicolas Chevalier
=======
** Last update Sat Jun  4 02:55:42 2016 Paul Wery
>>>>>>> master
*/

#include <sys/stat.h>
#include <fcntl.h>
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
  int		fd;

  line = NULL;
  if ((fd = open(".my_teemo", O_CREAT | O_TRUNC | O_WRONLY,
		 S_IRUSR | S_IWUSR)) == -1)
    return (-1);
  while (equal(elem->next->tab[0], line) == 0)
    {
      if (line != NULL)
	{
	  if (write(fd, line, my_strlen(line)) == -1
	      || write(fd, "\n", 1) == -1)
	    return (-1);
	  free(line);
	}
      my_putstr("? ");
      if ((line = get_next_line()) == NULL)
	return (-1);
    }
  close(fd);
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
	    return (0);
	  if (loop(elem) == -1)
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

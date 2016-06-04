/*
** echo_star.c for echo_star in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 04:06:44 2016 Paul Wery
** Last update Sat Jun  4 23:22:35 2016 Paul Wery
*/

#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

char		*create_replace_b(DIR *directory, t_elems *e, int size)
{
  t_order	*order;
  t_order	*it;
  char		*replace;
  int		n;

  n = 0;
  if ((replace = malloc(1)) == NULL
      || (order = order_names(directory)) == NULL)
    return (NULL);
  replace[0] = '\0';
  it = order->next;
  while (it != order)
    {
      if (match_elem_brak(it->name, e->one, e->two, e->ref) == 1)
	{
	  size += my_strlen(it->name) + my_strlen(e->path) + 1;
	  if ((replace = realloc(replace, size)) == NULL)
	    return (NULL);
	  n = create_replace_q_next(e->path, it->name, n, replace);
	}
      it = it->next;
    }
  closedir(directory);
  delete_order(&order);
  return (replace);
}

char	*one(char *buffer, int start, int end)
{
  char	*one;
  int	n;

  n = 0;
  while (start > 0 && buffer[start] != '/'
	 && buffer[start] != ' ' && buffer[start] != '\t')
    start -= 1;
  if (buffer[start] == ' ' || buffer[start] == '\t' || buffer[start] == '/')
    start += 1;
  if ((one = malloc(end - start + 1)) == NULL)
    return (NULL);
  while (start < end)
    one[n++] = buffer[start++];
  one[n] = '\0';
  return (one);
}

char	*two(char *buffer, int start, int end)
{
  char	*two;
  int	n;

  n = 0;
  while (buffer[end] != '\0' && buffer[end] != ' '
	 && buffer[end] != '\t')
    end += 1;
  start += 1;
  if ((two = malloc(end - start + 1)) == NULL)
    return (NULL);
  while (start < end)
    two[n++] = buffer[start++];
  two[n] = '\0';
  return (two);
}

char	*ref(char *buffer, int start, int end)
{
  char	*ref;
  int	n;

  n = 0;
  if ((ref = malloc(end - start + 2)) == NULL)
    return (NULL);
  while (start <= end)
    ref[n++] = buffer[start++];
  ref[n] = '\0';
  return (ref);
}

char		*echo_bracket(char *buffer, int *error)
{
  DIR		*directory;
  char		*replace;
  t_elems	e;

  e.l.start = 0;
  e.l.end = 0;
  while (glob_three(buffer, &e.l) != -1)
    {
      if ((e.one = one(buffer, e.l.start, e.l.start)) == NULL
	  || (e.two = two(buffer, e.l.end, e.l.end)) == NULL
	  || (e.ref = ref(buffer, e.l.start, e.l.end)) == NULL
	  || (e.path = get_elem_path(buffer, e.l.start, e.l.start)) == NULL)
	return (NULL);
      if ((e.path[0] == '\0' && (directory = opendir("./")) == NULL)
	  || (e.path[0] != '\0' && (directory = opendir(e.path)) == NULL))
	return (buffer);
      if ((replace = create_replace_b(directory, &e, 1)) == NULL
	  || (buffer = replace_seg_b(buffer, replace, error, e.l.start)) == NULL)
	return (NULL);
      free(e.path);
      free(e.one);
      free(e.two);
      free(e.ref);
    }
  return (buffer);
}

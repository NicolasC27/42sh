/*
** echo_star.c for echo_star in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 04:06:44 2016 Paul Wery
** Last update Sat Jun  4 23:19:07 2016 Paul Wery
*/

#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	create_replace_q_next(char *path, char *name, int n, char *replace)
{
  int	i;

  i = 0;
  while (path[i] != '\0')
    replace[n++] = path[i++];
  i = 0;
  while (name[i] != '\0')
    replace[n++] = name[i++];
  replace[n++] = ' ';
  replace[n] = '\0';
  return (n);
}

char		*create_replace_q(DIR *directory, char *elem, char *path, int size)
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
      if (match_elem(it->name, elem) == 1)
	{
	  size += my_strlen(it->name) + my_strlen(path) + 1;
	  if ((replace = realloc(replace, size)) == NULL)
	    return (NULL);
	  n = create_replace_q_next(path, it->name, n, replace);
	}
      it = it->next;
    }
  closedir(directory);
  delete_order(&order);
  return (replace);
}

char	*get_elem(char *buffer, int start, int end)
{
  char	*elem;
  int	n;

  n = 0;
  while (buffer[end] != '\0' && buffer[end] != ' ' && buffer[end] != '\t')
    end += 1;
  while (start > 0 && buffer[start] != ' ' && buffer[start] != '\t'
	 && buffer[start] != '/')
    start -= 1;
  if (buffer[start] == ' ' || buffer[start] == '\t' || buffer[start] == '/')
    start += 1;
  if ((elem = malloc(end - start + 1)) == NULL)
    return (NULL);
  while (start < end)
    elem[n++] = buffer[start++];
  elem[n] = '\0';
  return (elem);
}

char	*get_elem_path(char *buffer, int start, int end)
{
  char	*path;
  int	n;

  n = 0;
  while (end > 0 && buffer[end] != ' ' && buffer[end] != '\t'
	 && buffer[end] != '/')
    end -= 1;
  start = end;
  if (buffer[end] == ' ' || buffer[end] == '\t' || buffer[end] == '/')
    end += 1;
  while (start > 0 && buffer[start] != ' ' && buffer[start] != '\t')
    start -= 1;
  if (buffer[start] == ' ' || buffer[start] == '\t')
    start += 1;
  if ((path = malloc(end - start + 1)) == NULL)
    return (NULL);
  while (start < end)
    path[n++] = buffer[start++];
  path[n] = '\0';
  return (path);
}

char		*echo_quest(char *buffer, int *error)
{
  DIR		*directory;
  char		*elem;
  char		*path;
  char		*replace;
  int		start;

  start = -1;
  while ((start = glob_two(buffer, start + 1)) != -1)
    {
      if ((elem = get_elem(buffer, start, start)) == NULL
	  || (path = get_elem_path(buffer, start, start)) == NULL)
	return (NULL);
      if ((path[0] == '\0' && (directory = opendir("./")) == NULL)
	  || (path[0] != '\0' && (directory = opendir(path)) == NULL))
	return (buffer);
      if ((replace = create_replace_q(directory, elem, path, 1)) == NULL
	  || (buffer = replace_seg_q(buffer, replace, error, start)) == NULL)
	return (NULL);
      free(path);
      free(elem);
    }
  return (buffer);
}

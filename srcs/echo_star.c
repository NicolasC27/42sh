/*
** echo_star.c for echo_star in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 04:06:44 2016 Paul Wery
** Last update Wed Jun  1 04:24:37 2016 Paul Wery
*/

#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_ext(char *buffer, int start, int end)
{
  char	*ext;
  int	n;

  n = 0;
  while (buffer[start] != '*' && buffer[start] != '\0')
    start += 1;
  if ((ext = malloc(end - start + 1)) == NULL)
    return (NULL);
  while (start < end)
    ext[n++] = buffer[start++];
  ext[n] = '\0';
  return (ext);
}

char	*get_path(char *buffer, int start)
{
  char	*path;
  int	size;
  int	n;

  n = 0;
  size = start;
  while (buffer[size] != '*' && buffer[size] != '\0')
    size += 1;
  if ((path = malloc(size - start + 1)) == NULL)
    return (NULL);
  while (start < size)
    path[n++] = buffer[start++];
  path[n] = '\0';
  return (path);
}

int	echo_star(char buffer, int start, int end)
{
  char	*path;
  char	*ext;

  if ((path = get_path(buffer, start)) == NULL
      || (ext = get_ext(buffer, start, end)) == NULL)
    return (-1);
}

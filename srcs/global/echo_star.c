/*
** echo_star.c for echo_star in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 04:06:44 2016 Paul Wery
** Last update Wed Jun  1 22:52:18 2016 Paul Wery
*/

#include <glob.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

char	*get_ext_d(char *buffer, int start, int end)
{
  char	*ext;
  int	n;

  n = 0;
  while (buffer[start] != '*' && buffer[start] != '\0')
    start += 1;
  start += 1;
  if ((ext = malloc(end - start + 1)) == NULL)
    return (NULL);
  while (start < end)
    ext[n++] = buffer[start++];
  ext[n] = '\0';
  return (ext);
}

char	*get_path_d(char *buffer, int start)
{
  char	*path;
  int	size;
  int	n;

  n = 0;
  size = 0;
  while (buffer[size] != '*' && buffer[size] != '\0')
    size += 1;
  start = size;
  while (start > 0 && buffer[start] != ' ' && buffer[start] != '\t')
    start -= 1;
  if (buffer[start] == ' ' || buffer[start] == '\t')
    start += 1;
  if ((path = malloc(size - start + 1)) == NULL)
    return (NULL);
  while (start < size)
    path[n++] = buffer[start++];
  path[n] = '\0';
  return (path);
}

int	valid_ext(char *name, char *ref)
{
  int	n;
  int	i;

  n = 0;
  i = 0;
  if (name[n] == '.')
    return (0);
  if (ref[0] == '\0')
    return (1);
  while (name[n] != '\0')
    n += 1;
  while (n > 0 && name[n] != '.')
    n -= 1;
  if (n == 0)
    return (0);
  while (name[n] != '\0' && ref[i] != '\0' && name[n] == ref[i])
    {
      n += 1;
      i += 1;
    }
  if (name[n] == '\0' && ref[i] == '\0')
    return (1);
  return (0);
}

char	*create_replace(DIR *directory, char *ext, t_dir *file, int size)
{
  char	*replace;
  int	n;
  int	i;

  n = 0;
  if ((replace = malloc(1)) == NULL)
    return (NULL);
  replace[0] = '\0';
  while ((file = readdir(directory)) != NULL)
    {
      i = 0;
      if (valid_ext(file->d_name, ext) == 1)
	{
	  size += my_strlen(file->d_name) + 1;
	  if ((replace = realloc(replace, size)) == NULL)
	    return (NULL);
	  while (file->d_name[i] != '\0')
	    replace[n++] = file->d_name[i++];
	  replace[n++] = ' ';
	  replace[n] = '\0';
	}
    }
  closedir(directory);
  return (replace);
}

char		*echo_star(char *buffer, int start, int end)
{
  DIR		*directory;
  char		*path;
  char		*ext;
  char		*replace;

  while (valid_star(buffer) == 1)
    {
      if ((path = get_path_d(buffer, start)) == NULL
	  || (ext = get_ext_d(buffer, start, end)) == NULL)
	return (NULL);
      if ((path[0] == '\0' && (directory = opendir("./")) == NULL)
	  || (path[0] != '\0' && (directory = opendir(path)) == NULL))
	return (buffer);
      if ((replace = create_replace(directory, ext, NULL, 1)) == NULL
	  || (buffer = replace_seg(buffer, replace)) == NULL)
	return (NULL);
      free(path);
      free(ext);
    }
  return (buffer);
}

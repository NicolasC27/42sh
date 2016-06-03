/*
** echo_star.c for echo_star in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 04:06:44 2016 Paul Wery
** Last update Fri Jun  3 05:02:34 2016 Paul Wery
*/

#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

char	*get_ext_v(char *buffer, int start, int end)
{
  char	*ext;
  int	n;

  n = 0;
  while (buffer[start] != '$' && buffer[start] != '\0')
    start += 1;
  start += 1;
  end = start;
  while (buffer[end] != '\0' && buffer[end] != ' ' && buffer[end] != '\t')
    end += 1;
  if ((ext = malloc(end - start + 1)) == NULL)
    return (NULL);
  while (start < end)
    ext[n++] = buffer[start++];
  ext[n] = '\0';
  return (ext);
}

char	*create_replace_v(char *ext, int size, char **env, int num)
{
  char	*replace;
  int	n;
  int	i;

  n = 0;
  if ((replace = malloc(3)) == NULL)
    return (NULL);
  replace[0] = '\0';
  size += my_strlen(env[num]) - my_strlen(ext);
  if ((replace = realloc(replace, size)) == NULL)
    return (NULL);
  i = 0;
  while (env[num][i] != '=')
    i += 1;
  i += 1;
  while (env[num][i] != '\0')
    replace[n++] = env[num][i++];
  replace[n++] = ' ';
  replace[n] = '\0';
  return (replace);
}

int	valid_var(char *buffer)
{
  int	n;

  n = 0;
  while (buffer[n] != '\0' && buffer[n] != '$')
    n += 1;
  if (buffer[n] == '$' && buffer[n + 1] != '\0'
      && buffer[n + 1] != ' ' && buffer[n + 1] != '\t')
    return (1);
  return (0);
}

char		*echo_var(char *buffer, int *error, char **env)
{
  char		*ext;
  char		*replace;
  int		num;

  while (valid_var(buffer) == 1)
    {
      if ((ext = get_ext_v(buffer, 0, 0)) == NULL
	  || (num = find_set_unset(env, ext)) == -1)
	return (NULL);
      if (env[num] == NULL)
	{
	  *error = -2;
	  free(ext);
	  return (buffer);
	}
      if ((replace = create_replace_v(ext, 1, env, num)) == NULL
	  || (buffer = replace_seg_v(buffer, replace)) == NULL)
	return (NULL);
      free(ext);
    }
  return (buffer);
}

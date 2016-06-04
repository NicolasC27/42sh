/*
** echo_star.c for echo_star in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 04:06:44 2016 Paul Wery
** Last update Sat Jun  4 05:17:07 2016 Paul Wery
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

char	*create_replace_v(char *ext, int size, t_env *ev, int num)
{
  char	*replace;
  int	n;
  int	i;

  n = 0;
  if ((replace = malloc(3)) == NULL)
    return (NULL);
  replace[0] = '\0';
  size += my_strlen(ev->env[num]) - my_strlen(ext);
  if ((replace = realloc(replace, size)) == NULL)
    return (NULL);
  i = 0;
  while (ev->env[num][i] != '=')
    i += 1;
  i += 1;
  while (ev->env[num][i] != '\0')
    replace[n++] = ev->env[num][i++];
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

int	check_loc(char *buffer)
{
  int	n;

  n = 0;
  while (buffer[n] != '\0' && buffer[n] != '$')
    n += 1;
  if (buffer[n + 1] != '\0' && buffer[n + 1] == '?'
      && buffer[n + 2] == '\0')
    return (1);
  if (buffer[n + 1] != '\0' && buffer[n + 1] == '$'
      && buffer[n + 2] == '\0')
    return (2);
  return (0);
}

char		*echo_var(char *buffer, int *error, t_env *ev)
{
  char		*ext;
  char		*replace;
  int		num;

  while (valid_var(buffer) == 1)
    {
      if ((ext = get_ext_v(buffer, 0, 0)) == NULL
	  || (num = find_set_unset(ev->env, ext)) == -1)
	return (NULL);
      if (ev->env[num] == NULL && check_loc(buffer) == 0)
	{
	  *error = -2;
	  free(ext);
	  return (buffer);
	}
      if ((check_loc(buffer) == 0
	   && (replace = create_replace_v(ext, 1, ev, num)) == NULL)
	  || (check_loc(buffer) != 0
	      && (replace = get_val_ret(ev->val_exit, buffer)) == NULL)
	  || (buffer = replace_seg_v(buffer, replace)) == NULL)
	return (NULL);
      free(ext);
    }
  return (buffer);
}

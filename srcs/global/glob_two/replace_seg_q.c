/*
** replace_seg.c for replace_seg in /home/wery_p/rendu/PSU_2015_42sh/srcs/global
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 22:09:07 2016 Paul Wery
** Last update Fri Jun  3 23:20:51 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	glob_two(char *buffer, int start)
{
  while (buffer[start] != '\0')
    {
      if (buffer[start] == '?')
        return (start);
      start += 1;
    }
  return (-1);
}

int	match_elem(char *name, char *ref)
{
  int	n;

  n = 0;
  if (name[0] == '.')
    return (0);
  while ((name[n] == ref[n] || ref[n] == '?')
	 && name[n] != '\0' && ref[n] != '\0')
    n += 1;
  if (name[n] == '\0' && ref[n] == '\0')
    return (1);
  return (0);
}

int	size_q(char *buffer, char *replace, int start)
{
  int	end;

  end = start;
  while (start > 0 && buffer[start] != ' ' && buffer[start] != '\t'
	 && buffer[start])
    start -= 1;
  if (buffer[start] == ' ' || buffer[start] == '\t')
    start += 1;
  while (buffer[end] != '\0' && buffer[end] != ' ' && buffer[end] != '\t')
    end += 1;
  return (my_strlen(buffer) - (end - start) + my_strlen(replace) + 1);
}

char	*replace_seg_q_next(char *buffer, char *replace, int start)
{
  char	*result;
  int	n;
  int	i;

  n = 0;
  i = 0;
  if ((result = malloc(size_q(buffer, replace, start))) == NULL)
    return (NULL);
  while (start > 0 && buffer[start] != ' ' && buffer[start] != '\t')
    start -= 1;
  if (buffer[start] == ' ' || buffer[start] == '\t')
    start += 1;
  while (n < start)
    result[n++] = buffer[i++];
  i = 0;
  while (replace[i] != '\0')
    result[n++] = replace[i++];
  i = start;
  while (buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '\t')
    i += 1;
  while (buffer[i] != '\0')
    result[n++] = buffer[i++];
  result[n] = '\0';
  return (result);
}

char	*replace_seg_q(char *buffer, char *replace, int *error, int start)
{
  char	*result;

  if (replace[0] == '\0')
    {
      *error = -4;
      free(replace);
      return (buffer);
    }
  result = replace_seg_q_next(buffer, replace, start);
  free(buffer);
  free(replace);
  return (result);
}

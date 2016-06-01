/*
** replace_seg.c for replace_seg in /home/wery_p/rendu/PSU_2015_42sh/srcs/global
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 22:09:07 2016 Paul Wery
** Last update Wed Jun  1 23:26:25 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	valid_star(char *buffer)
{
  int	n;

  n = 0;
  while (buffer[n] != '*' && buffer[n] != '\0')
    n += 1;
  if (buffer[n] == '*')
    return (1);
  return (0);
}

int	end_elem(char *buffer)
{
  int	end;

  end = 0;
  while (buffer[end] != '*' && buffer[end] != '\0')
    end += 1;
  while (buffer[end] != ' ' && buffer[end] != '\t' && buffer[end] != '\0')
    end += 1;
  return (end);
}

int	start_elem(char *buffer)
{
  int	start;

  start = 0;
  while (buffer[start] != '*' && buffer[start] != '\0')
    start += 1;
  while (start > 0 && buffer[start] != ' ' && buffer[start] != '\t')
    start -= 1;
  if (buffer[start] == ' ' || buffer[start] == '\t')
    start += 1;
  return (start);
}

int	size_result(char *buffer, char *replace)
{
  int	start;
  int	end;

  start = 0;
  while (buffer[start] != '*' && buffer[start] != '\0')
    start += 1;
  end = start;
  while (buffer[end] != ' ' && buffer[end] != '\t' && buffer[end] != '\0')
    end += 1;
  while (start > 0 && buffer[start] != ' ' && buffer[start] != '\t')
    start -= 1;
  if (buffer[start] == ' ' || buffer[start] == '\t')
    start += 1;
  return (my_strlen(buffer) - (end - start) + my_strlen(replace));
}

char	*replace_seg(char *buffer, char *replace)
{
  char	*result;
  int	n;
  int	i;

  n = 0;
  i = 0;
  if ((result = malloc(size_result(buffer, replace) + 1)) == NULL)
    return (NULL);
  while (n < start_elem(buffer))
    result[n++] = buffer[i++];
  i = 0;
  while (replace[i] != '\0')
    result[n++] = replace[i++];
  i = 0;
  while (i < end_elem(buffer))
    i += 1;
  while (buffer[i] != '\0')
    result[n++] = buffer[i++];
  result[n] = '\0';
  free(buffer);
  free(replace);
  return (result);
}

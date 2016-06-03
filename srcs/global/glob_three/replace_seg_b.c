/*
** replace_seg.c for replace_seg in /home/wery_p/rendu/PSU_2015_42sh/srcs/global
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jun  1 22:09:07 2016 Paul Wery
** Last update Sat Jun  4 01:06:43 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	glob_three(char *buffer, t_limit *l)
{
  while (buffer[l->end] != '\0')
    {
      if (buffer[l->end] == '[')
	{
	  l->start = l->end;
	  while (buffer[l->end] != '\0' && buffer[l->end] != ' '
		 && buffer[l->end] != '\t' && buffer[l->end] != ']')
	    l->end += 1;
	  if (buffer[l->end] == ']')
	    return (1);
	}
      if (buffer[l->end] != '\0')
	l->end += 1;
    }
  return (-1);
}

char	*replace_seg_b(char *buffer, char *replace, int *error, int start)
{
  char	*result;

  if (replace[0] == '\0')
    {
      *error = -8;
      free(replace);
      return (buffer);
    }
  result = replace_seg_q_next(buffer, replace, start);
  free(buffer);
  free(replace);
  return (result);
}

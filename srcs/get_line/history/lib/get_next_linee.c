/*
** get_next_line.c for 42sh in /home/gerard_v/Documents/42sh/srcs/lib
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "history.h"

char	*my_reallocc(char *src, int size)
{
  char	*dest;
  int	i;

  i = 0;
  if ((dest = malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = '\0';
  free(src);
  return (dest);
}

char	*fill_line(char *buffer, int *cursor, int *size, t_prog *prog)
{
  while ((*size = read(prog->fd, buffer, READ_SIZE)) > 0)
    {
      prog->return_line[prog->i] = '\0';
      if ((prog->return_line = my_reallocc(prog->return_line,
					  READ_SIZE * prog->k++)) == NULL)
	return (NULL);
      while (*cursor < *size)
	{
	  if (buffer[*cursor] == '\n')
	    {
	      prog->return_line[prog->i] = '\0';
	      *cursor += 1;
	      return (prog->return_line);
	    }
	  prog->return_line[prog->i++] = buffer[(*cursor)++];
	}
      *cursor = 0;
    }
  if (prog->i > 0)
    {
      prog->return_line[prog->i] = '\0';
      return (prog->return_line);
    }
  free(prog->return_line);
  return (NULL);
}

int	emptying_buffer(char *buffer, int *cursor, int *size, t_prog *prog)
{
  while (*cursor < *size)
    {
      if (buffer[*cursor] == '\n')
	{
	  *cursor += 1;
	  prog->return_line[prog->i] = '\0';
	  return (1);
	}
      prog->return_line[prog->i] = buffer[*cursor];
      prog->i++;
      *cursor += 1;
    }
  *cursor = 0;
  return (0);
}

char		*get_next_linee(const int fd)
{
  static char	buffer[READ_SIZE];
  static int	cursor;
  static int	size;
  t_prog	prog;

  prog.i = 0;
  prog.k = 2;
  prog.fd = fd;
  if ((prog.return_line = malloc(sizeof(char) * READ_SIZE + 1)) == NULL)
    return (NULL);
  if (emptying_buffer(buffer, &cursor, &size, &prog) == 1)
    return (prog.return_line);
  return (fill_line(buffer, &cursor, &size, &prog));
}

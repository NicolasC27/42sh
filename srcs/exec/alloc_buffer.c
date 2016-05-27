/*
** alloc_buffer.c for alloc_buffer in /home/wery_p/rendu/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Apr  2 08:55:04 2016 Paul Wery
** Last update Sat Apr  2 09:18:26 2016 Paul Wery
*/

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	*realloc_w(char *str, int new_size)
{
  char	*buffer;
  int	n;

  n = 0;
  if ((buffer = malloc(new_size)) == NULL)
    return (NULL);
  while (n < (new_size - 1))
    {
      buffer[n] = str[n];
      n = n + 1;
    }
  while (n < new_size)
    {
      buffer[n] = '\0';
      n = n + 1;
    }
  free(str);
  return (buffer);
}

char		*alloc_buffer(char *file, int fd)
{
  char		*buffer;
  t_stat	my_stat;

  stat(file, &my_stat);
  if ((buffer = malloc((int)my_stat.st_size)) == NULL)
    return (NULL);
  if (read(fd, buffer, (int)my_stat.st_size) == -1)
    return (NULL);
  if ((buffer = realloc_w(buffer, (int)my_stat.st_size + 1)) == NULL)
    return (NULL);
  close(fd);
  return (buffer);
}

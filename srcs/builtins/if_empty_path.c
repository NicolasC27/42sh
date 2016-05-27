/*
** if_empty_path.c for if_empty_path in /home/wery_p/rendu/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri Apr  8 16:53:29 2016 Paul Wery
** Last update Fri Apr  8 17:47:52 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

char	*build_path(char *path, char *exec)
{
  char	*new_path;
  int	i;
  int	n;

  i = 0;
  n = 0;
  if ((new_path = malloc(my_strlen(path) + my_strlen(exec) + 2)) == NULL)
    return (NULL);
  while (i < my_strlen(path))
    new_path[i++] = path[n++];
  if (path[i - 1] != 47)
    new_path[i++] = 47;
  new_path[i] = '\0';
  n = 0;
  while (n < my_strlen(exec))
    new_path[i++] = exec[n++];
  new_path[i] = '\0';
  return (new_path);
}

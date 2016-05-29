/*
** make_path.c for make_path in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue Jan 19 17:55:41 2016 Paul Wery
** Last update Sun May 29 01:55:42 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

char	*final_path(char *path, char *exec)
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
  free(path);
  return (new_path);
}

int	nb_path(int n, char **env)
{
  int	i;
  int	z;

  i = 0;
  z = 0;
  if (env[n] == NULL)
    return (0);
  while (env[n][i] != '=' && env[n][i] != '\0')
    i += 1;
  if (env[n][i] != '\0')
    i += 1;
  while (env[n][i] != '\0')
    {
      while (env[n][i] != ':' && env[n][i] != '\0')
	i += 1;
      if (env[n][i] == ':')
	i += 1;
      z += 1;
    }
  return (z);
}

int	size_path(int n, int nb_t, char **env)
{
  int	i;
  int	z;
  int	size;

  i = 0;
  z = 1;
  size = 0;
  while (env[n][i] != '\0' && z <= nb_t)
    {
      while (env[n][i] != ':' && env[n][i] != '\0')
	{
	  i += 1;
	  if (z == nb_t)
	    size += 1;
	}
      if (env[n][i] != '\0')
	i += 1;
      z += 1;
    }
  return (size);
}

char	*get_path(int n, int nb_t, char **env, int i)
{
  char	*path;
  int	z;
  int	y;

  z = 1;
  y = 0;
  if ((path = malloc(size_path(n, nb_t, env) + 1)) == NULL)
    return (NULL);
  while (env[n][i] != '=' && env[n][i] != '\0')
    i += 1;
  i += 1;
  while (env[n][i] != '\0' && z <= nb_t)
    {
      while (env[n][i] != ':' && env[n][i] != '\0')
	{
	  if (z == nb_t)
	    path[y++] = env[n][i];
	  i += 1;
	}
      if (env[n][i] != '\0')
	i += 1;
      z += 1;
    }
  path[y] = '\0';
  return (path);
}

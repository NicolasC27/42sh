/*
** set_env.c for set_env in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri Jan 22 18:33:53 2016 Paul Wery
** Last update Wed Jun  1 02:51:24 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	add_env(char **cop, char **opts, int n)
{
  int	i;
  int	y;

  i = 0;
  y = 0;
  while (opts[1][i] != '\0')
    {
      cop[n][i] = opts[1][i];
      i += 1;
    }
  cop[n][i++] = '=';
  if (opts[2] != NULL)
    while (opts[2][y] != '\0')
      cop[n][i++] = opts[2][y++];
  cop[n][i] = '\0';
}

char	**realloc_part_env2(char **env, char **opts, int n, int i)
{
  char	*cop;

  if ((cop = malloc(my_strlen(opts[1]) + 2)) == NULL)
    return (NULL);
  while (opts[1][i] != '\0')
    {
      cop[i] = opts[1][i];
      i += 1;
    }
  cop[i++] = '=';
  cop[i] = '\0';
  free(env[n]);
  env[n] = cop;
  return (env);
}

char	**realloc_part_env(char **env, char **opts, int n, int i)
{
  char	*cop;
  int	y;

  y = 0;
  if (opts[2] != NULL)
    {
      if ((cop = malloc(my_strlen(opts[1]) + my_strlen(opts[2]) + 2)) == NULL)
	return (NULL);
      while (opts[1][i] != '\0')
	{
	  cop[i] = opts[1][i];
	  i += 1;
	}
      cop[i++] = '=';
      while (opts[2][y] != '\0')
	cop[i++] = opts[2][y++];
      cop[i] = '\0';
      free(env[n]);
      env[n] = cop;
    }
  else
    if ((env = realloc_part_env2(env, opts, n, i)) == NULL)
      return (NULL);
  return (env);
}

char	**realloc_env(char **env, int size, int n, char **opts)
{
  char	**cop;
  int	i;

  if ((cop = malloc(size * sizeof(char*))) == NULL)
    return (NULL);
  while (env[n] != NULL)
    {
      i = 0;
      if ((cop[n] = malloc(my_strlen(env[n]) + 1)) == NULL)
	return (NULL);
      while (env[n][i] != '\0')
	{
	  cop[n][i] = env[n][i];
	  i += 1;
	}
      cop[n][i] = '\0';
      n += 1;
    }
  if ((cop[n] = malloc(my_strlen(opts[1]) + my_strlen(opts[2]) + 2)) == NULL)
    return (NULL);
  add_env(cop, opts, n);
  cop[n + 1] = NULL;
  free_opts(env);
  return (cop);
}

char	**set_env(char *exec, char **opts, t_env *ev)
{
  int	n;
  int	size;

  size = 0;
  while (opts[size] != NULL)
    size += 1;
  if (comp_builtins(exec, "setenv") == 1 && (size == 3 || size == 2)
      && valid_name(opts[1], ev) == 0)
    {
      if ((n = find_set_unset(ev->env, opts[1])) == -1)
        return (NULL);
      if (ev->env[n] == NULL)
	{
	  if (opts[2] != NULL)
	    if ((ev->env = realloc_env(ev->env, n + 2, 0, opts)) == NULL)
	      return (NULL);
	  if (opts[2] == NULL)
	    if ((ev->env = realloc_env2(ev->env, n + 2, 0, opts)) == NULL)
	      return (NULL);
	}
      else
	if ((ev->env = realloc_part_env(ev->env, opts, n, 0)) == NULL)
	  return (NULL);
    }
  return (ev->env);
}

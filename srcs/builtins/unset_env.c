/*
** unset_env.c for unset_env in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri Jan 22 19:46:56 2016 Paul Wery
** Last update Fri Apr  8 19:51:24 2016 Paul Wery
*/


#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	cop_opt(char *cop, char *opt)
{
  int	n;

  n = 0;
  while (opt[n] != '\0')
    {
      cop[n] = opt[n];
      n += 1;
    }
  cop[n] = '=';
  cop[n + 1] = '\0';
}

void	use_cop(char **cop, char **env, int n, int i)
{
  int	y;

  y = 0;
  while (env[n][y] != '\0')
    {
      cop[i][y] = env[n][y];
      y += 1;
    }
  cop[i][y] = '\0';
}

char	**clear_env(char **env, int n, int size, int i)
{
  char	**cop;

  if ((cop = malloc(size * sizeof(char*))) == NULL)
    return (NULL);
  while (env[n] != NULL)
    {
      if (env[n][0] == '\0')
	n += 1;
      if (env[n] != NULL)
	{
	  if ((cop[i] = malloc(my_strlen(env[n]) + 1)) == NULL)
	    return (NULL);
	  use_cop(cop, env, n, i);
	  n += 1;
	  i += 1;
	}
    }
  free_opts(env);
  cop[i] = NULL;
  return (cop);
}

int	find_set_unset(char **env, char *opt)
{
  int	n;
  int	ret;
  char	*cop;

  n = 0;
  ret = 0;
  if ((cop = malloc(my_strlen(opt) + 2)) == NULL)
    return (-1);
  cop_opt(cop, opt);
  while (env[n] != NULL && ret == 0)
    {
      ret = comp_words(env[n], opt);
      if (ret == 0)
	n += 1;
    }
  free(cop);
  return (n);
}

char	**unset_env(char *exec, char **opts, char **env, int state)
{
  int	n;
  int	i;

  if (comp_builtins(exec, "unsetenv") == 1)
    {
      while (opts[state] != NULL)
	{
	  i = 0;
	  if ((n = find_set_unset(env, opts[state])) == -1)
	    return (NULL);
	  if (env[n] == NULL && opts[state + 1] == NULL)
	    return (env);
	  while (env[i] != NULL)
	    i += 1;
	  if (env[n] != NULL)
	    {
	      env[n][0] = '\0';
	      if ((env = clear_env(env, 0, i, 0)) == NULL)
		return (NULL);
	    }
	  state += 1;
	}
    }
  return (env);
}

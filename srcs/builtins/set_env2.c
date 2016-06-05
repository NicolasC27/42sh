/*
** set_env2.c for set_env2 in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sun Jan 24 16:08:56 2016 Paul Wery
** Last update Sun Jun  5 16:38:37 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <unistd.h>
#include "function.h"
#include "mins.h"

char	**realloc_env2(char **env, int size, int n, char **opts)
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
  if ((cop[n] = malloc(my_strlen(opts[1]) + 2)) == NULL)
    return (NULL);
  add_env(cop, opts, n);
  cop[n + 1] = NULL;
  free_opts(env);
  return (cop);
}

int	valid_name(char *name, t_env *ev)
{
  int	n;

  n = 0;
  while (name[n] != '\0')
    {
      if ((name[n] > 47 && name[n] < 58)
	  || (name[n] > 64 && name[n] < 91)
	  || (name[n] > 96 && name[n] < 123))
	n += 1;
      else
	{
	  ev->val_exit = 1;
	  my_put_error("setenv: ");
	  my_put_error("Variable name must contain alphanumeric characters.\n");
	  return (1);
	}
    }
  return (0);
}

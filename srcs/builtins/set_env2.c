/*
** set_env2.c for set_env2 in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sun Jan 24 16:08:56 2016 Paul Wery
** Last update Tue May 31 12:39:34 2016 Nicolas Chevalier
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

/*
** create_my_env.c for create_my_env in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 22:07:49 2016 Paul Wery
** Last update Tue May 31 12:39:00 2016 Nicolas Chevalier
*/

#include <unistd.h>
#include <stdlib.h>
#include "function.h"
#include "mins.h"

int	build_env(char **str, char **env, int n)
{
  int	i;

  while (str[n] != NULL)
    {
      i = 0;
      while (str[n][i] != '\0')
	i += 1;
      if (i > 0)
        {
          if ((env[n] = malloc(i + 1)) == NULL)
            return (1);
          env[n][i] = '\0';
        }
      n += 1;
    }
  return (0);
}

int	nb_env(char **str)
{
  int	n;

  n = 0;
  while (str[n] != NULL)
    n += 1;
  return (n);
}

char	*regroup_str(char *one, char *two, int state)
{
  char	*result;
  int	n;
  int	i;

  n = 0;
  i = 0;
  if ((result = malloc(my_strlen(one) + my_strlen(two) + 1)) == NULL)
    return (NULL);
  while (one[i] != '\0')
    result[n++] = one[i++];
  i = 0;
  while (two[i] != '\0')
    result[n++] = two[i++];
  result[n] = '\0';
  if (state == 1)
    free(two);
  return (result);
}

char	**create_my_env(char **str, int n, int i)
{
  char	**env;

  if (nb_env(str) != 0)
    {
      if ((env = malloc((nb_env(str) + 1) * sizeof(char *))) == NULL
	  || build_env(str, env, 0) == 1)
	return (NULL);
      while (str[i] != NULL)
	{
	  n = 0;
	  while (str[i][n] != '\0')
	    {
	      env[i][n] = str[i][n];
	      n += 1;
	    }
	  i += 1;
	}
      env[i] = NULL;
    }
  if ((env = final_env(str, env)) == NULL)
    return (NULL);
  return (env);
}

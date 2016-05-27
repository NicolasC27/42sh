/*
** final_env.c for final_env in /home/wery_p/rendu/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri Apr  8 19:53:29 2016 Paul Wery
** Last update Sat Apr  9 01:33:25 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

char	**full_pwd(char **env, int n)
{
  char	**opts;

  if ((opts = malloc(4 * sizeof(char*))) == NULL)
    return (NULL);
  opts[3] = NULL;
  if ((opts[0] = conv_str("setenv")) == NULL
      || (n = find_set_unset(env, "PWD")) == -1
      || (opts[1] = conv_str("PWD")) == NULL)
    return (NULL);
  if (env[n] == NULL || env[n][0] == '\0')
    {
      if ((opts[2] = ini_elem()) == NULL)
	return (NULL);
      if ((env = set_env("setenv", opts, env)) == NULL)
	return (NULL);
    }
  else
    opts[2] = NULL;
  free_opts(opts);
  return (env);
}

char	**full_path(char **env, int n)
{
  char	**opts;

  if ((opts = malloc(4 * sizeof(char*))) == NULL)
    return (NULL);
  opts[3] = NULL;
  if ((opts[0] = conv_str("setenv")) == NULL
      || (n = find_set_unset(env, "PATH")) == -1
      || (opts[1] = conv_str("PATH")) == NULL)
    return (NULL);
  if (env[n] == NULL || env[n][0] == '\0')
    {
      if ((opts[2] = conv_strs("/bin:/sbin:/usr/bin:/usr/sbin",
			       ":/usr/heimdal/bin:/usr/heimdal",
			       "/sbin")) == NULL)
	return (NULL);
      if ((env = set_env("setenv", opts, env)) == NULL)
	return (NULL);
    }
  else
    opts[2] = NULL;
  free_opts(opts);
  return (env);
}

char	**final_env(char **str, char **env)
{
  if (nb_env(str) == 0)
    {
      if ((env = malloc(1 * sizeof(char*))) == NULL)
        return (NULL);
      env[0] = NULL;
    }
  if ((env = full_path(env, 0)) == NULL
      || (env = full_pwd(env, 0)) == NULL)
    return (NULL);
  return (env);
}

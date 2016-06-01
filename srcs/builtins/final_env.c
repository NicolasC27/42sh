/*
** final_env.c for final_env in /home/wery_p/rendu/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Fri Apr  8 19:53:29 2016 Paul Wery
** Last update Wed Jun  1 02:57:53 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

char	**full_pwd(t_env *ev, int n)
{
  char	**opts;

  if ((opts = malloc(4 * sizeof(char*))) == NULL)
    return (NULL);
  opts[3] = NULL;
  if ((opts[0] = conv_str("setenv")) == NULL
      || (n = find_set_unset(ev->env, "PWD")) == -1
      || (opts[1] = conv_str("PWD")) == NULL)
    return (NULL);
  if (ev->env[n] == NULL || ev->env[n][0] == '\0')
    {
      if ((opts[2] = ini_elem()) == NULL)
	return (NULL);
      if ((ev->env = set_env("setenv", opts, ev)) == NULL)
	return (NULL);
    }
  else
    opts[2] = NULL;
  free_opts(opts);
  return (ev->env);
}

char	**full_path(t_env *ev, int n)
{
  char	**opts;

  if ((opts = malloc(4 * sizeof(char*))) == NULL)
    return (NULL);
  opts[3] = NULL;
  if ((opts[0] = conv_str("setenv")) == NULL
      || (n = find_set_unset(ev->env, "PATH")) == -1
      || (opts[1] = conv_str("PATH")) == NULL)
    return (NULL);
  if (ev->env[n] == NULL || ev->env[n][0] == '\0')
    {
      if ((opts[2] = conv_strs("/bin:/sbin:/usr/bin:/usr/sbin",
			       ":/usr/heimdal/bin:/usr/heimdal",
			       "/sbin")) == NULL)
	return (NULL);
      if ((ev->env = set_env("setenv", opts, ev)) == NULL)
	return (NULL);
    }
  else
    opts[2] = NULL;
  free_opts(opts);
  return (ev->env);
}

char	**final_env(char **str, t_env *ev)
{
  if (nb_env(str) == 0)
    {
      if ((ev->env = malloc(1 * sizeof(char*))) == NULL)
        return (NULL);
      ev->env[0] = NULL;
    }
  if ((ev->env = full_path(ev, 0)) == NULL
      || (ev->env = full_pwd(ev, 0)) == NULL)
    return (NULL);
  return (ev->env);
}

/*
** cd_return.c for cd_return in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Mar 16 18:13:32 2016 Paul Wery
<<<<<<< HEAD
** Last update Tue May 31 12:39:48 2016 Nicolas Chevalier
=======
** Last update Wed Jun  1 02:53:25 2016 Paul Wery
>>>>>>> master
*/

#include <stdlib.h>
#include <unistd.h>
#include "function.h"
#include "mins.h"

int	get_start_elem(char **env, int n)
{
  int	i;

  i = 0;
  while (env[n][i] != '=' && env[n][i] != '\0')
    i += 1;
  if (env[n][i] != '\0')
    i += 1;
  return (i);
}

char	*get_elem_env(char **env, char *opt, int n, int i)
{
  char	*elem;
  int	size;

  size = 0;
  if ((n = find_set_unset(env, opt)) == -1)
    return (NULL);
  i = get_start_elem(env, n);
  while (env[n][i] != '\0')
    {
      i += 1;
      size += 1;
    }
  if ((elem = malloc(size + 1)) == NULL)
    return (NULL);
  i = get_start_elem(env, n);
  size = 0;
  while (env[n][i] != '\0')
    elem[size++] = env[n][i++];
  elem[size] = '\0';
  return (elem);
}

char	*create_opt(char *opt)
{
  char	*cop;
  int	n;

  n = 0;
  if ((cop = malloc(my_strlen(opt) + 1)) == NULL)
    return (NULL);
  while (opt[n] != '\0')
    {
      cop[n] = opt[n];
      n += 1;
    }
  cop[n] = '\0';
  return (cop);
}

char	**swap_elems(char *pwd, t_env *ev)
{
  char	**opts;

  if ((opts = malloc(sizeof(char*) * 4)) == NULL ||
      (opts[0] = create_opt("full")) == NULL ||
      (opts[1] = create_opt("PWD")) == NULL ||
      (opts[2] = create_opt(pwd)) == NULL)
    return (NULL);
  opts[3] = NULL;
  if ((ev->env = set_env("setenv", opts, ev)) == NULL)
    return (NULL);
  free_opts(opts);
  return (ev->env);
}

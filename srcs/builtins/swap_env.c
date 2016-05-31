/*
** swap_env.c for swap_env in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Mar 17 00:54:45 2016 Paul Wery
** Last update Tue May 31 12:41:33 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <unistd.h>
#include "function.h"
#include "mins.h"

char	*ini_elem(void)
{
  char	*elem;
  int	n;

  n = 0;
  if ((elem = malloc(200)) == NULL)
    return (NULL);
  while (n < 200)
    elem[n++] = '\0';
  if (getcwd(elem, 200) == NULL)
    return (NULL);
  return (elem);
}

char	*concat_with_home(char *opt, t_env *ev)
{
  char	*result;
  char	*home;
  int	n;
  int	i;

  if ((home = get_elem_env(ev->env, "HOME", 0, 0)) == NULL
      || (result = malloc(my_strlen(home) + my_strlen(opt))) == NULL)
    return (NULL);
  n = 0;
  i = 1;
  while (home[n] != '\0')
    {
      result[n] = home[n];
      n += 1;
    }
  while (opt[i] != '\0')
    result[n++] = opt[i++];
  result[n] = '\0';
  free(home);
  free(opt);
  return (result);
}

char	**moove_directory(char **opts, t_env *ev)
{
  char	*pwd;

  if (opts[1][0] == '~'
      && (opts[1] = concat_with_home(opts[1], ev)) == NULL)
    return (NULL);
  if (chdir((const char*)opts[1]) == -1)
    {
      ev->val_exit = 1;
      my_put_error(opts[1]);
      my_put_error(": Permission non accordée.\n");
      return (ev->env);
    }
  if (ev->oldpwd != NULL)
    free(ev->oldpwd);
  if ((ev->oldpwd = get_elem_env(ev->env, "PWD", 0, 0)) == NULL ||
      (pwd = ini_elem()) == NULL)
    return (NULL);
  if ((ev->env = swap_elems(pwd, ev->env)))
    free(pwd);
  return (ev->env);
}

char	**actualize_pwd(char **opts, t_env *ev)
{
  if (opts[1][0] == '-' && opts[1][1] == '\0' &&
      ev->oldpwd == NULL)
    {
      ev->val_exit = 1;
      my_putstr("cd: OLDPWD not set\n");
      return (ev->env);
    }
  if ((opts[1][0] != '-' || opts[1][1] != '\0') &&
      (ev->env = moove_directory(opts, ev)) == NULL)
    return (NULL);
  if (opts[1][0] == '-' && opts[1][1] == '\0' &&
      (ev->env = moove_old_directory(ev)) == NULL)
    return (NULL);
  return (ev->env);
}

char	**swap_env(char *exec, char **opts, t_env *ev)
{
  int	n;

  if ((n = find_set_unset(ev->env, "PWD")) == -1)
    return (NULL);
  if (ev->env[n] == NULL)
    return (ev->env);
  if (comp_builtins(exec, "cd") == 1 && opts[1] != NULL
      && opts[2] == NULL)
    {
      if ((ev->env = actualize_pwd(opts, ev)) == NULL)
	return (NULL);
    }
  else if (comp_builtins(exec, "cd") == 1 && opts[1] == NULL)
    if ((ev->env = moove_home(ev)) == NULL)
      return (NULL);
  return (ev->env);
}

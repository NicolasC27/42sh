/*
** fonc_cd.c for fonc_cd in /home/wery_p/rendu/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Apr  2 01:01:53 2016 Paul Wery
** Last update Mon May 30 22:09:16 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

char	**moove_old_directory(t_env *ev)
{
  char	*pwd;

  if (chdir((const char*)ev->oldpwd) == -1)
    {
      ev->val_exit = 1;
      my_put_error(ev->oldpwd);
      my_put_error(": Permission denied.\n");
      return (ev->env);
    }
  free(ev->oldpwd);
  if ((ev->oldpwd = get_elem_env(ev->env, "PWD", 0, 0)) == NULL ||
      (pwd = ini_elem()) == NULL)
    return (NULL);
  if ((ev->env = swap_elems(pwd, ev->env)) == NULL)
    return (NULL);
  free(pwd);
  return (ev->env);
}

char	**moove_home(t_env *ev)
{
  char	*pwd;

  if (ev->env[find_set_unset(ev->env, "HOME")] == NULL)
    return (ev->env);
  if (ev->oldpwd != NULL)
    free(ev->oldpwd);
  if ((pwd = get_elem_env(ev->env, "HOME", 0, 0)) == NULL)
    return (NULL);
  if (chdir((const char*)pwd) == -1)
    {
      ev->val_exit = 1;
      my_put_error(pwd);
      my_put_error(": Permission denied.\n");
      return (ev->env);
    }
  if ((ev->oldpwd = get_elem_env(ev->env, "PWD", 0, 0)) == NULL)
    return (NULL);
  if ((ev->env = swap_elems(pwd, ev->env)) == NULL)
    return (NULL);
  free(pwd);
  return (ev->env);
}

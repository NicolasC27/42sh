/*
** my_put_error.c for my_put_error in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed Jan 20 02:49:57 2016 Paul Wery
** Last update Fri Jun  3 05:01:16 2016 Paul Wery
*/

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	my_put_error(char *error)
{
  write(2, error, my_strlen(error));
}

void	aff_error(char *exec)
{
  my_put_error(exec);
  if (errno == EACCES)
    my_put_error(": Permission denied.\n");
  else if (errno == ENOEXEC)
    my_put_error(": Exec format error. Binary file not executable.\n");
  else if (errno == ENAMETOOLONG)
    my_put_error(": File name too long.\n");
  else
    my_put_error(": Command not found.\n");
  exit(1);
}

void	aff_cd_error(char *exec, t_env *ev)
{
  ev->val_exit = 1;
  my_put_error(exec);
  if (errno == EACCES)
    my_put_error(": Permission denied.\n");
  else if (errno == ENOENT)
    my_put_error(": No such file or directory.\n");
  else if (errno == ENOTDIR)
    my_put_error(": Not a directory.\n");
  else if (errno == ENAMETOOLONG)
    my_put_error(": Path name too long.\n");
  else
    my_put_error(": Permission denied.\n");
}

int	notm_next(t_exec *it, t_env *ev, int n)
{
  char	c[2];
  int	i;

  i = 0;
  c[1] = '\0';
  if (it->tab[n] == NULL)
    return (0);
  while (it->tab[n][i] != '$')
    i += 1;
  i += 1;
  while (it->tab[n][i] != '\0' && it->tab[n][i] != ' '
	 && it->tab[n][i] != '\t')
    {
      c[0] = it->tab[n][i++];
      my_put_error(c);
    }
  my_put_error(": Undefined variable.\n");
  ev->val_exit = 1;
  return (1);
}

int	notm(t_exec *it, t_env *ev, int n, int i)
{
  if (it->error == -1 || it->error == -3)
    {
      my_put_error(it->tab[0]);
      my_put_error(": No match.\n");
      ev->val_exit = 1;
      return (1);
    }
  else if (it->error == -2)
    {
      while (it->tab[n] != NULL && it->tab[n][i] != '$')
	{
	  i = 0;
	  while (it->tab[n][i] != '\0' && it->tab[n][i] != '$')
	    i += 1;
	  if (it->tab[n][i] == '\0')
	    n += 1;
	}
      if (notm_next(it, ev, n) == 1)
	return (1);
    }
  return (0);
}

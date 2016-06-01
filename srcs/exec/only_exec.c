/*
** only_exec.c for only_exec in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 11:55:15 2016 Paul Wery
** Last update Wed Jun  1 03:43:26 2016 Paul Wery
*/

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void		path_exec(char *exec, char **opts, char **env)
{
  struct stat	stat_t;
  int		ret;

  ret = stat(exec, &stat_t);
  if (access(exec, F_OK) != -1)
    {
      if (ret != -1 && S_ISDIR(stat_t.st_mode))
	{
	  my_put_error(exec);
	  my_put_error(": Permission denied.\n");
	  exit(1);
	}
      else
	execve((const char*)exec, opts, env);
    }
  else
    aff_error(exec);
}

int	where_exec(char *exec)
{
  int	n;

  n = 0;
  if (exec[0] == '.')
    {
      while (exec[n] == '.' && exec[n] != '\0')
	n += 1;
      if (exec[n] == '/')
	return (1);
    }
  if (exec[0] == '/')
    return (1);
  return (0);
}

void	get_status(int status, t_env *ev)
{
  if (WTERMSIG(status) == SIGSEGV)
    {
      my_putstr("Segmentation Fault\n");
      ev->val_exit = 139;
    }
  else
    ev->val_exit = WEXITSTATUS(status);
}

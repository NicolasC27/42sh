/*
** only_exec.c for only_exec in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 11:55:15 2016 Paul Wery
<<<<<<< HEAD
** Last update Tue May 31 12:38:20 2016 Nicolas Chevalier
=======
** Last update Thu Jun  2 01:03:37 2016 Paul Wery
>>>>>>> master
*/

#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "function.h"
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
	if (execve((const char*)exec, opts, env) == -1)
	  aff_error(exec);
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
      my_put_error("Segmentation Fault\n");
      ev->val_exit = 139;
    }
  else if (WTERMSIG(status) == SIGFPE)
    {
      my_put_error("Floating exception\n");
      ev->val_exit = 136;
    }
  else
    ev->val_exit = WEXITSTATUS(status);
}

/*
** only_exec.c for only_exec in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 11:55:15 2016 Paul Wery
** Last update Sun May 29 01:55:26 2016 Paul Wery
*/

#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

void	path_exec(char *exec, char **opts, char **env)
{

  if (access(exec, F_OK) != -1)
    execve((const char*)exec, opts, env);
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
    my_putstr("Segmentation Fault\n");
  ev->val_exit = WEXITSTATUS(status);
}

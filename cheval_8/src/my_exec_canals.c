/*
** my_exec_canals.c for my_execve_canals in /home/cheval_8/PSU_2015_minishell2
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Apr 12 20:57:17 2016 Chevalier Nicolas
** Last update Thu Apr 14 22:29:41 2016 Chevalier Nicolas
*/

#include <fcntl.h>
#include "my.h"

void		close_fd(int *pipe_fd)
{
  int		i;

  i = -1;
  if (pipe_fd != NULL)
    while (pipe_fd[++i] != 0)
      close(pipe_fd[i]);
}

int		redi_simple(t_redirection *redirection, int flags, int newfd)
{
  int		fd;

  fd = 0;
  if ((fd = open(redirection->tab[0], flags, 0644)) == -1)
    {
      if (newfd == 0)
	{
	  my_putstr(redirection->tab[0]);
	  my_putstr(" : Aucun fichier ou dossier de ce type.\n");
	}
      else
	my_putstr("Error open\n");
      exit (0);
    }
  if (dup2(fd, newfd) == -1)
    my_putstr("error dup2");
  return (fd);
}

int		my_execve_canals(t_command *command, t_redirection **redirection)
{
  int		z;

  z = -1;
  (command->input != -1) ? dup2(command->input, 0) : (0);
  (command->output != -1) ? dup2(command->output, 1) : (0);
  if (redirection != NULL)
    while (++z < command->nb_redirection)
      {
	if (redirection[z]->redi_two_right == 1)
	  redi_simple(redirection[z], O_CREAT | O_RDWR | O_APPEND, 1);
	else if (redirection[z]->redi_left == 1)
	  redi_simple(redirection[z], O_RDONLY, 0);
        else if (redirection[z]->redi_right == 1)
	  redi_simple(redirection[z], O_CREAT | O_RDWR | O_TRUNC, 1);
      }
  return (0);
}

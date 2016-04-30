/*
** wait.c for wait.c in /home/cheval_8/PSU_2015_minishell2
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Apr 12 21:58:09 2016 Chevalier Nicolas
** Last update Tue Apr 12 22:00:14 2016 Chevalier Nicolas
*/

#include <sys/wait.h>
#include "my.h"

void		loop_wait(int nb_exec)
{
  int		status;

  while (nb_exec-- > 0)
    {
      status = 0;
      if (wait(&status) == -1)
	my_putstr("ERROR");
      if (WTERMSIG(status) == 11)
	my_putstr_err("Segmentation fault (core dumped)\n");
      if (WIFSTOPPED(status))
	my_putstr_err("Stopped\n");
    }
}

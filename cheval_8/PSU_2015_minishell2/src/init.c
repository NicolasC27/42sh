/*
** init.c for init.c in /home/cheval_8/PSU_2015_minishell2
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Apr 12 21:30:41 2016 Chevalier Nicolas
** Last update Thu Apr 14 02:52:43 2016 Chevalier Nicolas
*/

#include "my.h"

void		init_struct_redirection(t_command **command, int z)
{
  (*command)->redirection[z]->redi_right = 0;
  (*command)->redirection[z]->redi_left = 0;
  (*command)->redirection[z]->redi_two_right = 0;
}

void		init_struct(t_command *tmp)
{
  tmp->output = -1;
  tmp->input = -1;
  tmp->fd = -1;
}

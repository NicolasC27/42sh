/*
** list.c for list.c in /home/cheval_8/rendu/PSU_2015_minishell2/lib/src/list
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Apr  2 18:14:21 2016 Chevalier Nicolas
** Last update Tue Apr 12 23:03:24 2016 Chevalier Nicolas
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

void		init_list(t_list *list)
{
  list->first = NULL;
  list->last = NULL;
}

int		my_insert_pipe(t_command **list, t_command *command)
{
  (*list)->output = command->output;
  (*list)->input = command->input;
  (*list)->fd = command->fd;
  return (0);
}

int		my_insert_pushfront(t_list *list, t_command *command)
{
  t_command	*tmp;

  if ((tmp = malloc(sizeof(t_command))) == NULL)
    return (0);
  tmp->data = command->data;
  tmp->output = command->output;
  tmp->input = command->input;
  tmp->fd = command->fd;
  tmp->prev = list->last;
  tmp->next = NULL;
  if (list->last)
    list->last->next = tmp;
  else
    list->first = tmp;
  list->last = tmp;
  return (1);
}

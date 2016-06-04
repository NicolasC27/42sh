/*
** add_command.c for 42sh in /home/gerard_v/Documents/42sh/srcs/commands
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "history.h"

int    	add_command_first(t_commands *commands, t_cmd *cmd)
{
  t_cmd	*new_cmd;

  new_cmd = malloc(sizeof(t_cmd));
  if (new_cmd == NULL)
    return (1);
  new_cmd->command = cmd->command;
  new_cmd->length = cmd->length;
  new_cmd->prev = commands->first;
  new_cmd->next = commands->last;
  commands->first = new_cmd;
  commands->last = new_cmd;
  commands->size++;
  return (0);
}

int    	add_command_last(t_commands *commands, t_cmd *cmd)
{
  t_cmd	*new_cmd;

  new_cmd = malloc(sizeof(t_cmd));
  if (new_cmd == NULL)
    return (1);
  new_cmd->command = cmd->command;
  new_cmd->length = cmd->length;
  new_cmd->next = NULL;
  new_cmd->prev = commands->last;
  commands->last->next = new_cmd;
  commands->last = new_cmd;
  commands->size++;
  return (0);
}

int	add_command(t_commands *commands, t_cmd *cmd)
{
  if (commands->size == 0)
    {
      if (add_command_first(commands, cmd) == 1)
	return (1);
    }
  else if (commands->size > 0)
    {
      if (add_command_last(commands, cmd) == 1)
	return (1);
    }
  return (0);
}

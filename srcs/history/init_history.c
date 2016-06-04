/*
** init_history.c for 42sh in /home/gerard_v/Documents/42sh/srcs
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "history.h"

/*void	search_command(t_history *history)
{
  char	key[1];

  history->current_cmd = history->commands.last;
  canonical_mode(&history->oldt, &history->newt, 0);
  read(0, key, 1);
  while (key[0] != 10)
    {
      read(0, key, 1);
      if (key[0] == 65 && history->current_cmd != NULL &&
	  history->current_cmd->prev != NULL)
	{
	  history->current_cmd = history->current_cmd->prev;
	  my_putstr(history->current_cmd->command, 1);
	}
      else if (key[0] == 66 && history->current_cmd != NULL &&
	       history->current_cmd->next != NULL)
	{
	  history->current_cmd = history->current_cmd->next;
	  my_putstr(history->current_cmd->command, 1);
	}
    }
  canonical_mode(&history->oldt, &history->newt, 1);
  }*/

void	init_commands(t_history *history)
{
  history->commands.first = NULL;
  history->commands.last = NULL;
  history->commands.size = 0;
  history->press = 0;
  history->current_cmd = NULL;
}

int  	init_history(t_history *history)
{
  init_commands(history);
  if (read_file(&history->commands) == 1)
    return (1);
  history->current_cmd = history->commands.last;
  /*if (write_file(&history->commands) == 1)
    {
      free_commands(&history->commands);
      return (1);
    }
    free_commands(&history->commands);*/
  return (0);
}

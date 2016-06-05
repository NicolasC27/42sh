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
  return (0);
}

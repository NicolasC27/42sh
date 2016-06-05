/*
** write_file.c for 42sh in /home/gerard_v/Documents/42sh/srcs/file
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "history.h"

int	write_file(t_history *history)
{
  int	open_fd;
  int	close_fd;
  int	ret;
  t_cmd	*cmd_tmp;

  open_fd = open_file(history->history_file, 1);
  if (open_fd == -1)
    return (open_error(history->history_file));
  cmd_tmp = history->commands.first;
  while (cmd_tmp)
    {
      ret = write(open_fd, cmd_tmp->command, my_strlen(cmd_tmp->command));
      ret = write(open_fd, "\n", 1);
      if (ret == 0 || ret == -1)
	{
	  my_putstr("Error : Write failed\n", 2);
	  return (1);
	}
      cmd_tmp = cmd_tmp->next;
    }
  close_fd = close_file(open_fd);
  if (close_fd == -1)
    return (close_error(history->history_file));
  return (0);
}

/*
** read_file.c for 42sh in /home/gerard_v/Documents/42sh/srcs/file
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Sun Jun  5 16:13:11 2016 Nicolas Chevalier
*/

#include "history.h"

int	add_command_history(t_commands *commands, char *buffer)
{
  t_cmd	cmd;

  if (buffer[0] == '\0')
    return (0);
  cmd.command = strdup(buffer);
  cmd.length = my_strlen(buffer);
  if (add_command(commands, &cmd) == 1)
    return (1);
  return (0);
}

int	check_line(char *buffer)
{
  int	i;

  i = 0;
  while (buffer[i] != '\0')
    {
      if (buffer[i] < '!' && buffer[i] > '~')
	return (1);
      i++;
    }
  return (0);
}

int	read_file(t_history *history)
{
  int	open_fd;
  int	close_fd;
  char	*buffer;

  open_fd = open_file(history->history_file, 0);
  if (open_fd == -1)
    return (open_error(history->history_file));
  while ((buffer = get_next_linee(open_fd))!= NULL)
    {
      if (check_line(buffer) == 1 ||
	  add_command_history(&history->commands, buffer) == 1)
	{
	  my_putstr_out("Error : Read failed\n", 2);
	  return (1);
	}
      free(buffer);
    }
  close_fd = close_file(open_fd);
  if (close_fd == -1)
    return (close_error(history->history_file));
  return (0);
}

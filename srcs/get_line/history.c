/*
** history.c for history.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 18:21:53 2016 Nicolas Chevalier
** Last update Sat Jun  4 23:12:43 2016 Nicolas Chevalier
*/

#include <curses.h>
#include <term.h>
#include "history.h"
#include "get_line.h"

int		history_func(t_edit *line, t_history *history, char *buff)
{
  char	*el;
  char	*move_left;
  int	fd;

  if (line->len != 0 && line->pos != 0)
      return (EXIT_FAILURE);
  fd = open("/dev/tty", O_RDWR);
  move_left = tigetstr("cub1");
  el = tigetstr("el");
  if  (buff[2] == 'A' && history->current_cmd != NULL &&
       history->current_cmd->prev != NULL)
    {
      while (line->len != 0)
	{
	  write(fd, move_left, my_strlen(move_left));
	  line->len -= 1;
	}
      write(fd, el, my_strlen(el));
      history->current_cmd = history->current_cmd->prev;
      line->cmd = strdup(history->current_cmd->command);
      line->len = history->current_cmd->length;
      my_putstr(line->cmd);
    }
  else if (buff[2] == 'B' && history->current_cmd != NULL &&
       history->current_cmd->next != NULL)
    {
      while (line->len != 0)
	{
	  write(fd, move_left, my_strlen(move_left));
	  line->len -= 1;
	}
      write(fd, el, my_strlen(el));
      history->current_cmd = history->current_cmd->next;
      line->cmd = strdup(history->current_cmd->command);
      line->len = history->current_cmd->length;
      my_putstr(line->cmd);
    }
}

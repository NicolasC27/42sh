/*
** history.c for history.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 18:21:53 2016 Nicolas Chevalier
** Last update Sat Jun  4 18:22:51 2016 Nicolas Chevalier
*/

#include <curses.h>
#include <term.h>
#include "history.h"
#include "get_line.h"

int		history_func(t_edit *line, t_history *history, char *buff)
{
  char	*el;
  char	*home;
  char	*save;
  int	fd;

  fd = open("/dev/tty", O_RDWR);
  save = tigetstr("rc");
  home = tigetstr("cub1");
  el = tigetstr("el");
  if  (buff[2] == 'A' && history->current_cmd != NULL &&
       history->current_cmd->prev != NULL)
    {
      write(fd, save, my_strlen(save));
      write(fd, el, my_strlen(el));
      history->current_cmd = history->current_cmd->prev;
      line->cmd = strdup(history->current_cmd->command);
      line->len = history->current_cmd->length;
      my_putstr(line->cmd);
    }
  else if (buff[2] == 'B' && history->current_cmd != NULL &&
       history->current_cmd->next != NULL)
    {
      write(fd, save, my_strlen(save));
      write(fd, el, my_strlen(el));
      history->current_cmd = history->current_cmd->next;
      line->cmd = strdup(history->current_cmd->command);
      line->len = history->current_cmd->length;
      my_putstr(line->cmd);
    }
}

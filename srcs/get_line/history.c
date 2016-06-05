/*
** history.c for history.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 18:21:53 2016 Nicolas Chevalier
** Last update Sun Jun  5 08:26:48 2016 Nicolas Chevalier
*/

#include <curses.h>
#include <term.h>
#include "history.h"
#include "get_line.h"

static void	key_up_func(t_edit *line, t_history *history, t_info *info)
{
  char		*el;

  el = tigetstr("el");
  while (line->len != 0)
    {
      write(info->fd, info->keyleft, my_strlen(info->keyleft));
      line->len -= 1;
    }
  write(info->fd, el, my_strlen(el));
  history->current_cmd = history->current_cmd->prev;
  line->cmd = strdup(history->current_cmd->command);
  line->len = history->current_cmd->length;
  my_putstr(line->cmd);
}

static void	key_down_func(t_edit *line, t_history *history, t_info *info)
{
  char		*el;

  el = tigetstr("el");
  while (line->len != 0)
    {
      write(info->fd, info->keyleft, my_strlen(info->keyleft));
      line->len -= 1;
    }
  write(info->fd, el, my_strlen(el));
  history->current_cmd = history->current_cmd->next;
  line->cmd = strdup(history->current_cmd->command);
  line->len = history->current_cmd->length;
  my_putstr(line->cmd);
}

int		history_func(t_edit *line, t_history *history, char *buff, t_info *info)
{
  if (line->len != 0 && line->pos != 0)
      return (EXIT_FAILURE);
  if  (buff[2] == 'A' && history->current_cmd != NULL &&
       history->current_cmd->prev != NULL)
    key_up_func(line, history, info);
  else if (buff[2] == 'B' && history->current_cmd != NULL &&
	   history->current_cmd->next != NULL)
    key_down_func(line, history, info);
}

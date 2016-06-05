/*
** history.c for history.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 18:21:53 2016 Nicolas Chevalier
** Last update Sun Jun  5 19:20:19 2016 Lucas Debouté
*/

#include <curses.h>
#include <term.h>
#include "history.h"
#include "function.h"
#include "get_line.h"

int		add_element_history(t_history *history, char *str)
{
  t_cmd		cmd;

  cmd.command = str;
  cmd.length = strlen(str);
  if (add_command(&history->commands, &cmd) == 1)
    return (1);
  history->current_cmd = history->commands.last;
  return (0);
}

static void	key_up_func(t_edit *line, t_history *history, t_info *info)
{
  char		*el;

  el = tigetstr("el");
  while (line->len != 0)
    {
      write(info->fd, info->keyleft, my_strlen(info->keyleft));
      line->len -= 1;
    }
  if (history->current_cmd != history->commands.first)
    history->current_cmd = history->current_cmd->prev;
  write(info->fd, el, my_strlen(el));
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
  if (history->current_cmd != history->commands.last)
    history->current_cmd = history->current_cmd->next;
  write(info->fd, el, my_strlen(el));
  line->cmd = strdup(history->current_cmd->command);
  line->len = history->current_cmd->length;
  my_putstr(line->cmd);
}

int		history_func(t_edit *line, t_history *history,
			     char *buff, t_info *info)
{
  if (line->len != 0 && line->pos != 0)
      return (EXIT_FAILURE);
  if  (buff[2] == 'A' && history->current_cmd != NULL)
    key_up_func(line, history, info);
  else if (buff[2] == 'B' && history->current_cmd != NULL)
    key_down_func(line, history, info);
  return (EXIT_SUCCESS);
}

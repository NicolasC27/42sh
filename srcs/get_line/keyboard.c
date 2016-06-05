/*
** history.c for keyboard.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:29:38 2016 Nicolas Chevalier
** Last update Sun Jun  5 15:23:13 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "get_line.h"

static int	is_key(char *buff, int ESC, int HOOK, int KEY)
{
  if (buff[1] == '\0')
    return (1);
  if (buff[0] == ESC && buff[1] == HOOK && buff[2] == KEY)
    return (0);
  return (1);

}

static void	control_a(t_edit *line, char *buff, t_info *info)
{
  int		i;

  i = line->len;
  while (line->pos != (line->len * -1))
    {
      write(info->fd, info->keyleft, my_strlen(info->keyleft));
      i -= 1;
      line->pos -= 1;
    }
}

static void	control_k(t_edit *line, char *buff, t_info *info)
{
  int		i;
  char		*s;

  s = tigetstr("el");
  write(info->fd, s, my_strlen(s));
  line->len += line->pos;
  line->cmd[line->len] = '\0';
  line->pos = 0;
}

static void	control_e(t_edit *line, char *buff, t_info *info)
{
  int		i;
  char		*s;

  i = line->len + line->pos;
  if (i != line->len)
    while (line->cmd[i])
      {
	write(info->fd, info->keyright, my_strlen(info->keyright));
	i += 1;
	line->pos += 1;
      }
}

int		keyboard(t_edit *line, char *buff, t_history *history, t_info *info)
{
  if (is_key(buff, 27, 91, UP) == 0 || is_key(buff, 27, 91, DOWN) == 0)
    history_func(line, history, buff, info);
  else if (is_key(buff, 27, 91, LEFT) == 0)
    cursors_left(line, info);
  else if (is_key(buff, 27, 91, RIGHT) == 0)
    cursors_right(line, info);
  else if (buff[0] == '\t')
    my_autocomplete(line->cmd);
  else if (buff[0] == 127)
    cursors_delete(line, buff, info);
  else if (buff[0] == CTRLA)
    control_a(line, buff, info);
  else if (buff[0] == CTRLK)
    control_k(line, buff, info);
  else if (buff[0] == CTRLE)
    control_e(line, buff, info);
}

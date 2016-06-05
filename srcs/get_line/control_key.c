/*
** control_key.c for control_key.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Jun  5 21:58:56 2016 Nicolas Chevalier
** Last update Sun Jun  5 21:59:21 2016 Nicolas Chevalier
*/

#include <ncurses.h>
#include "get_line.h"

void		control_ctrlleft(t_edit *line, t_info *info)
{
  int		i;

  i = line->len + line->pos;
  i -= 1;
  while (i >= 0 && (line->cmd[i] < 48 ||
		    (line->cmd[i] > 57 && line->cmd[i] < 65) ||
		    (line->cmd[i] > 90 && line->cmd[i] < 97) ||
		    (line->cmd[i] > 122 && line->cmd[i] < 127)))
    {
      write(info->fd, info->keyleft, my_strlen(info->keyleft));
      i -= 1;
      line->pos -= 1;
    }
  while (i >= 0 && ((line->cmd[i] > 47 && line->cmd[i] < 58) ||
		    (line->cmd[i] > 64 && line->cmd[i] < 91) ||
		    (line->cmd[i] > 96 && line->cmd[i] < 123) ||
		    (line->cmd[i] > 47 && line->cmd[i] < 57)))
    {
      write(info->fd, info->keyleft, my_strlen(info->keyleft));
      i -= 1;
      line->pos -= 1;
    }
}

static void	cursor_plus_one(t_edit *line, t_info *info)
{
  if (line->pos < 0)
    {
      write(info->fd, info->keyright, my_strlen(info->keyright));
      line->pos += 1;
    }
}

void		control_ctrlright(t_edit *line, t_info *info)
{
  int		i;

  i = line->len + line->pos;
  while (line->pos < 0 && (line->cmd[i] < 48 ||
			   (line->cmd[i] > 57 && line->cmd[i] < 65) ||
			   (line->cmd[i] > 90 && line->cmd[i] < 97) ||
			   (line->cmd[i] > 122 && line->cmd[i] < 127)))
    {
      write(info->fd, info->keyright, my_strlen(info->keyright));
      i += 1;
      line->pos += 1;
    }
  while (line->pos < 0 && ((line->cmd[i] > 47 && line->cmd[i] < 58) ||
			   (line->cmd[i] > 64 && line->cmd[i] < 91) ||
			   (line->cmd[i] > 96 && line->cmd[i] < 123) ||
			   (line->cmd[i] > 47 && line->cmd[i] < 57)))
    {
      write(info->fd, info->keyright, my_strlen(info->keyright));
      i += 1;
      line->pos += 1;
    }
  cursor_plus_one(line, info);
}

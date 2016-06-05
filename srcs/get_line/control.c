/*
** control.c for control.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Jun  5 16:26:00 2016 Nicolas Chevalier
** Last update Sun Jun  5 21:42:41 2016 Nicolas Chevalier
*/

#include <ncurses.h>
#include "get_line.h"

void		control_a(t_edit *line, t_info *info)
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

void		control_k(t_edit *line, t_info *info)
{
  char		*s;

  if (line->cmd != NULL)
    {
      s = tigetstr("el");
      write(info->fd, s, my_strlen(s));
      line->len += line->pos;
      line->cmd[line->len] = '\0';
      line->pos = 0;
    }
}

void		control_e(t_edit *line, t_info *info)
{
  int		i;

  i = line->len + line->pos;
  if (i != line->len)
    while (line->cmd[i])
      {
	write(info->fd, info->keyright, my_strlen(info->keyright));
	i += 1;
	line->pos += 1;
      }
}

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
  while (i >= 0 && ((line->cmd[i] > 64 && line->cmd[i] < 91) ||
		    (line->cmd[i] > 96 && line->cmd[i] < 123) ||
		    (line->cmd[i] > 47 && line->cmd[i] < 57)))
    {
      write(info->fd, info->keyleft, my_strlen(info->keyleft));
      i -= 1;
      line->pos -= 1;
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
  while (line->pos < 0 && ((line->cmd[i] > 64 && line->cmd[i] < 91) ||
		    (line->cmd[i] > 96 && line->cmd[i] < 123) ||
		    (line->cmd[i] > 47 && line->cmd[i] < 57)))
    {
      write(info->fd, info->keyright, my_strlen(info->keyright));
      i += 1;
      line->pos += 1;
    }
  if (line->pos < 0)
    {
      write(info->fd, info->keyright, my_strlen(info->keyright));
      i += 1;
      line->pos += 1;
    }
}

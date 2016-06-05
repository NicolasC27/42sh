/*
** control.c for control.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Jun  5 16:26:00 2016 Nicolas Chevalier
** Last update Sun Jun  5 16:26:41 2016 Nicolas Chevalier
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

  s = tigetstr("el");
  write(info->fd, s, my_strlen(s));
  line->len += line->pos;
  line->cmd[line->len] = '\0';
  line->pos = 0;
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

/*
** cursor.c for cursor.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 18:43:42 2016 Nicolas Chevalier
** Last update Sun Jun  5 08:29:46 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "get_line.h"

static int	manage_string(t_edit *line, t_info *info)
{
  char		*save;
  char		*buff;
  char		*tmp;
  int		i;
  int		j;

  buff = malloc(sizeof(char) * 1 * -(line->pos) + 1);
  i  = line->len + line->pos;
  j = 0;
  while (line->cmd[i])
    buff[j++] = line->cmd[i++];
  buff[j] = '\0';
  i = line->len + line->pos;
  line->cmd[i - 1] = '\0';
  tmp = strcat(line->cmd, buff);
  line->cmd = tmp;
  line->len -= 1;
  save = tigetstr("sc");
  write(info->fd, save, my_strlen(save));
  my_putstr(&line->cmd[i - 1]);
  save = tigetstr("rc");
  write(info->fd, save, my_strlen(save));
}

int		cursors_delete(t_edit *line, char *buff, t_info *info)
{
  char		*str;
  char		*s;
  int		i;

  i = 0;
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  i -= line->len;
  if (i == line->pos)
    return (EXIT_FAILURE);
  write(info->fd, info->keyleft, my_strlen(info->keyleft));
  s = tigetstr("el");
  write(info->fd, s, my_strlen(s));
  manage_string(line, info);
}

int		cursors_left(t_edit *line, t_info *info)
{
  char		*s;
  int		i;
  char		*save;


  i = 0;
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  i -= line->len;
  if (i == line->pos)
    return (EXIT_FAILURE);
  write(info->fd, info->keyleft, my_strlen(info->keyleft));
  line->pos -= 1;
  return (EXIT_SUCCESS);
}

int		cursors_right(t_edit *line, t_info *info)
{
  char		*s;

  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  if (line->cmd[line->len + (line->pos)] == '\0')
    return (EXIT_FAILURE);
  write(info->fd, info->keyright, my_strlen(info->keyright));
  line->pos += 1;
  return (0);
}

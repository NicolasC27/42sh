/*
** cursor.c for cursor.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 18:43:42 2016 Nicolas Chevalier
** Last update Sun Jun  5 21:38:03 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "function.h"
#include "get_line.h"

static int	manage_string(t_edit *line, t_info *info, int j, int i)
{
  char		*save;
  char		*buff;
  char		*tmp;

  if ((buff = malloc(sizeof(char) * 1 * -(line->pos) + 1)) == NULL)
    return (EXIT_FAILURE);
  i  = line->len + line->pos;
  while (line->cmd[i])
    buff[j++] = line->cmd[i++];
  buff[j] = '\0';
  i = line->len + line->pos;
  line->cmd[i - 1] = '\0';
  tmp = strcat(line->cmd, buff);
  free(buff);
  line->cmd = tmp;
  line->len -= 1;
  save = tigetstr("sc");
  if (save != NULL)
    write(info->fd, save, my_strlen(save));
  my_putstr(&line->cmd[i - 1]);
  save = tigetstr("rc");
  if (save != NULL)
    write(info->fd, save, my_strlen(save));
  return (EXIT_SUCCESS);
}

int		cursors_delete(t_edit *line, t_info *info)
{
  char		*s;
  int		i;

  i = 0;
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  i -= line->len;
  if (i == line->pos)
    return (EXIT_FAILURE);
  if (info->keyleft)
    write(info->fd, info->keyleft, my_strlen(info->keyleft));
  if ((s = tigetstr("el")) != NULL)
    write(info->fd, s, my_strlen(s));
  if (manage_string(line, info, 0, 0) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		cursors_left(t_edit *line, t_info *info)
{
  int		i;

  i = 0;
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  i -= line->len;
  if (i == line->pos)
    return (EXIT_FAILURE);
  if (info->keyleft != NULL)
    write(info->fd, info->keyleft, my_strlen(info->keyleft));
  line->pos -= 1;
  return (EXIT_SUCCESS);
}

int		cursors_right(t_edit *line, t_info *info)
{
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  if (line->cmd[line->len + (line->pos)] == '\0')
    return (EXIT_FAILURE);
  if (info->keyright != NULL)
    write(info->fd, info->keyright, my_strlen(info->keyright));
  line->pos += 1;
  return (EXIT_SUCCESS);
}

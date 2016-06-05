/*
** character.c for character.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Jun  5 02:04:38 2016 Nicolas Chevalier
** Last update Sun Jun  5 08:31:09 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <ncurses.h>
#include "get_line.h"

void		add_character_normal(t_edit *line, char c)
{
  line->cmd = realloc(line->cmd, line->len + 3);
  line->cmd[line->len] = c;
  line->cmd[line->len + 1] = '\0';
  line->len += 1;
}

static int	reset_terminal(t_edit *line, int i, t_info *info)
{
  char		*save;
  char		*el;

  save = tigetstr("sc");
  write(info->fd, save, my_strlen(save));
  el = tigetstr("el");
  write(info->fd, el, my_strlen(el));
  i += 1;
  my_putstr(&line->cmd[i]);
  save = tigetstr("rc");
  write(info->fd, save, my_strlen(save));
  return (EXIT_SUCCESS);
}

void		add_character_advanced(t_edit *line, char c, t_info *info)
{
  char		*tmp;
  int		j;
  int		i;

  tmp = NULL;
  if ((tmp = malloc(sizeof(char) * (line->len + 2))) == NULL)
    exit(EXIT_FAILURE);
  line->cmd = realloc(line->cmd, line->len + 2);
  j = 0;
  i = line->len + (line->pos);
  while (i >= 0 && line->cmd[i] && i != line->len)
    tmp[j++] = line->cmd[i++];
  tmp[j] = '\0';
  i = line->len + (line->pos);
  line->cmd[i] = c;
  line->cmd[i + 1] = '\0';
  line->cmd = strcat(line->cmd, tmp);
  line->len += 1;
  reset_terminal(line, i, info);
}

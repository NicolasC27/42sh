/*
** cursor.c for cursor.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 18:43:42 2016 Nicolas Chevalier
** Last update Sat Jun  4 23:36:57 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "get_line.h"

static int	manage_string(t_edit *line)
{
  char		*save;
  char		*buff;
  char		*tmp;
  int		i;
  int		j;

  buff = malloc(sizeof(char) * 1 * -(line->pos) + 1);
  i  = line->len + line->pos;
  j = 0; // salut
  while (line->cmd[i])
    {
      buff[j] = line->cmd[i];
      i += 1;
      j += 1;
    }
  buff[j] = '\0';
  i = line->len + line->pos;
  line->cmd[i - 1] = '\0';
  tmp = strcat(line->cmd, buff);
  line->cmd = tmp;
  line->len -= 1;
  save = tigetstr("sc");
  my_putstr(save);
  my_putstr(&line->cmd[i - 1]);
  save = tigetstr("rc");
  my_putstr(save);
}

int		cursors_delete(t_edit *line, char *buff)
{
  char		*str;
  char		*s;
  int		fd;
  int		i;

  i = 0;
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  i -= line->len;
  if (i == line->pos)
    return (EXIT_FAILURE);
  if ((fd = open("/dev/tty", O_RDWR)) == -1)
    return (EXIT_FAILURE);
  s = tigetstr("cub1");
  if (s != NULL)
    write(fd, s, my_strlen(s));
  s = tigetstr("el");
  if (s != NULL)
    write(fd, s, my_strlen(s));
  manage_string(line);
}

int		cursors_left(t_edit *line)
{
  static int	first;
  char		*s;
  int		fd;
  int		i;
  char		*save;


  i = 0;
  first = 1;
  if ((fd = open("/dev/tty", O_RDWR)) == -1)
    return (EXIT_FAILURE);
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  i -= line->len;
  if (i == line->pos)
    return (EXIT_FAILURE);
  s = tigetstr("cub1");
  if (s != NULL)
    write(fd, s, my_strlen(s));
  line->pos -= 1;
  return (EXIT_SUCCESS);
}

int		cursors_right(t_edit *line)
{
  char		*s;
  int		fd;

  if ((fd = open("/dev/tty", O_RDWR)) == -1)
    return (EXIT_FAILURE);
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  if (line->cmd[line->len + (line->pos)] == '\0')
    return (EXIT_FAILURE);
  s = tigetstr("cuf1");
  if (s != NULL)
    write(fd, s, my_strlen(s));
  line->pos += 1;
  return (0);
}

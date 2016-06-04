/*
** history.c for keyboard.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:29:38 2016 Nicolas Chevalier
** Last update Sat Jun  4 18:31:30 2016 Nicolas Chevalier
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

int		delete_string(t_edit *line)
{
  char		*str;
  char		*s;
  int		fd;
  int		i;

  i = 0;
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  if (line->len + (line->pos) == 0)
    return (EXIT_FAILURE);
  fd = open("/dev/tty", O_RDWR);
  s = tigetstr("cub1");
  write(fd, s, my_strlen(s));
  s = tigetstr("el");
  write(fd, s, my_strlen(s));
  line->cmd[line->len - 1] = '\0';
  line->len -= 1;
}

int		left(t_edit *line)
{
  char		*s;
  int		fd;
  int		i;
  char		*save;


  i = 0;
  fd = open("/dev/tty", O_RDWR);
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  i -= line->len;
  if (i == line->pos)
    return (EXIT_FAILURE);
  if (line->len + (line->pos) == 0)
    return (EXIT_FAILURE);
  s = tigetstr("cub1");
  write(fd, s, my_strlen(s));
  line->pos -= 1;
}

int		right(t_edit *line)
{
  char		*s;
  int		fd;

  fd = open("/dev/tty", O_RDWR);
  if (line->cmd == NULL)
    return (EXIT_FAILURE);
  if (line->cmd[line->len + (line->pos)] == '\0')
    return (EXIT_FAILURE);
  s = tigetstr("cuf1");
  write(fd, s, my_strlen(s));
  line->pos += 1;
  return (0);
}

int		keyboard(t_edit *line, char *buff, t_history *history)
{
  if (is_key(buff, 27, 91, UP) == 0 || is_key(buff, 27, 91, DOWN) == 0)
    history_func(line, history, buff);
  if (is_key(buff, 27, 91, LEFT))
    left(line);
  if (is_key(buff, 27, 91, RIGHT))
    right(line);
  if (buff[0] == '\t')
    my_autocomplete(line->cmd);
  if (buff[0] == 127)
    delete_string(line);
}

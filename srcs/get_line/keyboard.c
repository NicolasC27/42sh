/*
** history.c for keyboard.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:29:38 2016 Nicolas Chevalier
** Last update Sat Jun  4 23:40:15 2016 Nicolas Chevalier
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

static void	clear_screen_(void)
{
  char		*s;
  int		fd;

  fd = open("/dev/tty", O_RDWR);
  s = tigetstr("clear");
  write(fd, s, my_strlen(s));
  my_putstr("prompt$>");
}

int		keyboard(t_edit *line, char *buff, t_history *history)
{
  if (is_key(buff, 27, 91, UP) == 0 || is_key(buff, 27, 91, DOWN) == 0)
    history_func(line, history, buff);
  else if (is_key(buff, 27, 91, LEFT) == 0)
    cursors_left(line);
  else if (is_key(buff, 27, 91, RIGHT) == 0)
    cursors_right(line);
  else if (buff[0] == '\t')
     my_autocomplete(line->cmd);
  else if (buff[0] == 127)
    cursors_delete(line, buff);
  else if (buff[0] == 12)
    clear_screen_();
}

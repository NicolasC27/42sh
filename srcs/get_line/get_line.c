/*
** get_line.c for get_line.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:27:38 2016 Nicolas Chevalier
** Last update Sun Jun  5 03:09:41 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_line.h"
#include "function.h"
#include "history.h"

char		*return_str(char *str, t_history *history)
{
  char		*s;
  int		fd;
  char		*clear;

  fd = open("/dev/tty", O_RDWR);
  s = tigetstr("cud1");
  write(fd, s, my_strlen(s));
  clear = tigetstr("el");
  write(fd, clear, my_strlen(clear));
  s = tigetstr("cud1");
  write(fd, s, my_strlen(s));
  s = tigetstr("cuu1");
  write(fd, s, my_strlen(s));
  if (add_command_history(history->commands, str) == 1)
    return (NULL);
  return (str);
}

static int	check_key(char *buff)
{
  if (buff[0] != '\t' && buff[0] != '\n' && buff[0] != 127
      && buff[2] != LEFT && buff[2] != RIGHT
      && buff[2] != DOWN && buff[2] != UP
      && buff[0] != CLEAR)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

static void	manage_line(t_edit *line, t_info *info,
			    char buff[10], t_history *history)
{
  keyboard(line, buff, history);
  if (!check_key(buff))
    {
      if (line->pos == 0)
	add_character_normal(line, buff[0]);
      else
	add_character_advanced(line, buff[0]);
    }
}

char		*get_line(t_history *history)
{
  t_edit	line;
  t_info	info;
  char		buff[10];
  int		len;

  len = 1;
  if (isatty(0) == 0)
    return (get_next_line());
  init(&line);
  while (len > 0)
    {
      memset(buff, '\0', 9);
      if ((len = read(0, buff, 10)) == -1)
	return (NULL);
      buff[len] = '\0';
      if (!check_key(buff))
	my_putstr(buff);
      if (buff[0] == 4 && buff[1] == '\0')
	return (NULL);
      if (buff[0] == '\n')
	return (return_str(line.cmd, history));
      manage_line(&line, &info, buff, history);
    }
  return (line.cmd);
}

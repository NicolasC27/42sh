/*
** history.c for keyboard.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:29:38 2016 Nicolas Chevalier
** Last update Sat Jun  4 16:22:25 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <curses.h>
#include <term.h>
#include <fcntl.h>
#include <string.h>
#include "get_line.h"

static void	history(t_edit *line)
{
}

static int	is_key(char *buff, int ESC, int HOOK, int KEY)
{
  if (buff[1] == '\0')
    return (EXIT_FAILURE);
  if (buff[0] == ESC && buff[1] == HOOK && buff[2] == KEY)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);

}

static char	*my_autocomplete(char *str)
{
  struct dirent	*dirent;
  DIR		*dir;
  char		*s;
  char		*cursor;
  int		fd;
  int		i;
  int		x;
  int		y;
  char		*save;

  if ((dir = opendir("./")) == NULL)
    {
      my_putstr("ERROR");
      exit(EXIT_FAILURE);
    }
  x = 0;
  y = 0;
  fd = open("/dev/tty", O_RDWR);
  save = tigetstr("sc");
  write(fd, save, my_strlen(save));
  s = tigetstr("cud1");
  cursor = tgoto(s, 0, 0);
  i = -1;
  while (cursor[++i] != '\0');
  write(fd, cursor, i);
  while ((dirent = readdir(dir)))
    {
      if (dirent->d_name[0] != '.')
	{
	  write(fd, dirent->d_name, my_strlen(dirent->d_name));
	  my_putstr(" ");
	}
    }
  s = tigetstr("rc");
  write(fd, s, my_strlen(s));
}

void		delete_string(t_edit *line)
{
  char		*str;
  char		*s;
  int		fd;
  int		i;

  i = 0;
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
  s = tigetstr("cub1");
  write(fd, s, my_strlen(s));
  line->pos -= 1;
  /* save = tigetstr("sc"); */
  /* write(fd, save, my_strlen(save)); */
  /* s = tigetstr("el"); */
  /* write(fd, s, my_strlen(s)); */
  /* save = tigetstr("rc"); */
  /* write(fd, save, my_strlen(save)); */

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

int		keyboard(t_edit *line, char *buff)
{
  if (buff[0] && buff[1] != 0)
    {
      if (is_key(buff, 27, 91, UP) || is_key(buff, 27, 91, DOWN))
	history(line);
      if (is_key(buff, 27, 91, LEFT))
	left(line);
      if (is_key(buff, 27, 91, RIGHT))
	right(line);
    }
  if (buff[0] == '\t')
    my_autocomplete(line->cmd);
  if (buff[0] == 127)
    delete_string(line);
}

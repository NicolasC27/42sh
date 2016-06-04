/*
** history.c for keyboard.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:29:38 2016 Nicolas Chevalier
** Last update Sat Jun  4 05:02:58 2016 Nicolas Chevalier
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
  if (buff[0] == ESC && buff[1] == HOOK && buff[2] == KEY)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);

}

int		get_pos_(int *y, int fd)
{
  char		*buff;
  int		indice;
  int		len;
  int		i;
  char		num[10];
  char		num1[15];
  int		j;
  char		*s;

  i = 0;
  memset(buff, 30, 0);
  write(fd, "\033[6n", my_strlen("\033[6n"));
  len = read(fd, buff, 19);
  buff[len] = '\0';
  while (buff[i] == 27 && i < 100)
    i += 1;
  j = 0;
  i += 1;
  while (buff[i] && buff[i] != ';')
    {
      num[j] = buff[i];
      i += 1;
      j += 1;
    }
  num[j] = '\0';
  *y = atoi(num) - 1;
  i += 1;
  j = 0;
  while (buff[i] && buff[i] != 'R' && buff[i] != ';')
    {
      num1[j] = buff[i];
      i += 1;
      j += 1;
    }
  num1[j] = '\0';
  return (atoi(num1) - 1);
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
	write(fd, dirent->d_name, my_strlen(dirent->d_name));
      my_putstr("\t");
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
  /* write(fd, s, my_strlen(s)); */
  s = tigetstr("cub1");
  write(fd, s, my_strlen(s));
  s = tigetstr("el");
  write(fd, s, my_strlen(s));
  line->cmd[line->len - 1] = '\0';
  line->len -= 1;
}

void		left(t_edit *line)
{
  char		*s;
  int		fd;

  s = tigetstr("le");
  fd = open("/dev/tty", O_RDWR);
  write(fd, s, my_strlen(s));
}

void		right(t_edit *line)
{
  return (0);
}

int		keyboard(t_edit *line, char *buff)
{
  if (buff[0] != 27)
    return ;
  if (is_key(buff, 27, 91, UP) || is_key(buff, 27, 91, DOWN))
    history(line);
  if (is_key(buff, 27, 91, LEFT))
    left(line);
  if (is_key(buff, 27, 91, RIGHT))
    right(line);
  if (buff[0] == '\t')
    my_autocomplete(line->cmd);
  if (buff[0] == 127)
    delete_string(line);
}

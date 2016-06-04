/*
** autocomplete.c for autocomplete.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 18:25:11 2016 Nicolas Chevalier
** Last update Sat Jun  4 18:27:07 2016 Nicolas Chevalier
*/

#include <curses.h>
#include <term.h>
#include <dirent.h>
#include <fcntl.h>
#include "get_line.h"

char		*my_autocomplete(char *str)
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

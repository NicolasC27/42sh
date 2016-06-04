/*
** get_line.c for get_line.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:27:38 2016 Nicolas Chevalier
** Last update Sat Jun  4 15:57:10 2016 Nicolas Chevalier
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

char		*return_str(char *str)
{
  char		*s;
  char		buff[4096];
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
  return (str);
}

void		manage_pos()
{
  char		*s;
  char		*cursor;
  int		fd;
  int		i;

  s = tigetstr("cuu1");
  cursor = tgoto(s, 20, 20);
  fd = open("/dev/tty", O_RDWR);
  i = -1;
  while (cursor[++i] != '\0');
  write(fd, cursor, i);
}

char		*get_line(char **env, t_history *history)
{
  t_edit	line;
  t_info	info;
  char		buff[10];
  int		len;
  char		*stock;
  int		i;
  char		*save;
  char		*s;
  int		fd;
  int		j;

  j = 0;
  i = 0;
  len = 1;
  if ((isatty(0)) == 0)
    {
      stock = get_next_line();
      return (stock);
    }
  init(&line, &info, env);
  while (len > 0)
    {
      memset(buff, '\0', 9);
      if ((len = read(0, buff, 10)) == -1)
	return (NULL);
      buff[len] = '\0';
      if (buff[0] != '\t' && buff[0] != '\n' && buff[0] != 127
	  && buff[2] != LEFT && buff[2] != RIGHT
	  && buff[2] != DOWN && buff[2] != UP)
	my_putstr(buff);
      if (buff[0] == 4 && buff[1] == '\0')
	return (NULL);
      if (buff[0] == '\n')
	return (return_str(line.cmd));
      keyboard(&line, buff, history);
      /* manage_pos(); */
      if (buff[0] != '\t' && buff[0] != 127 && buff[2] != LEFT &&
	  buff[2] != RIGHT)
	{
	  if (line.pos == 0)
	    {
	      line.cmd = realloc(line.cmd, line.len + 10);
	      line.cmd[line.len] = buff[0];
	      line.cmd[line.len + 1] = '\0';
	      line.len += 1;
	    }
	  else
	    {
	      stock = NULL;
	      stock = malloc(sizeof(char) * (line.len + 2));
	      /* line.cmd = realloc(line.cmd, line.len + 1); */
	      j = 0;
	      i = line.len + (line.pos); // sadlut
	      while (line.cmd[i] && i != line.len)
		{
		  stock[j] = line.cmd[i];
		  j += 1;
		  i += 1;
		}
	      stock[j] = '\0';
	      i = line.len + (line.pos);
	      line.cmd[i] = buff[0];
	      line.cmd[i + 1] = '\0';
	      line.cmd = strcat(line.cmd, stock);
	      line.len += 1;
	      /* line.pos -= 1; */
	      fd = open("/dev/tty", O_RDWR);
	      save = tigetstr("sc");
	      write(fd, save, my_strlen(save));
	      s = tigetstr("el");
	      write(fd, s, my_strlen(s));
	      i += 1;
	      while (line.cmd[i])
		{
		  write(1, &line.cmd[i++], 1);
		}
	      /* my_putstr(&line.cmd[i + 1]); */
	      save = tigetstr("rc");
	      write(fd, save, my_strlen(save));
	    }
	}
    }
  return (line.cmd);
}

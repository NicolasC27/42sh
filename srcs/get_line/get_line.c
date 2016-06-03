/*
** get_line.c for get_line.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:27:38 2016 Nicolas Chevalier
** Last update Fri Jun  3 23:17:24 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "get_line.h"
#include "function.h"

char		*return_str(char *str)
{
  mode(0, 1, 0);
  return (str);
}

char		*get_line(char **env)
{
  t_edit	line;
  t_info	info;
  char		buff[10];
  int		len;
  char		*stock;

  len = 1;
  if ((isatty(0)) == 0)
    {
      stock = get_next_line();
      return (stock);
    }
  init(&line, &info, env);
  while (len > 0)
    {
      memset(buff, '\0', 7);
      if ((len = read(0, buff, 10)) == -1)
	return (NULL);
      buff[len] = '\0';
      if (buff[0] != '\t')
	my_putstr(buff);
      if (buff[0] == 4 && buff[1] == '\0')
	return (NULL);
      if (buff[0] == '\n')
	return (return_str(line.cmd));
      keyboard(&line, buff);
      line.cmd = realloc(line.cmd, line.len + 2);
      line.cmd[line.len] = buff[0];
      line.cmd[line.len + 1] = '\0';
      line.len += 1;
    }
  return (line.cmd);
}

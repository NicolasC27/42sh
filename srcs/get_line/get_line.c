/*
** get_line.c for get_line.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:27:38 2016 Nicolas Chevalier
** Last update Sun Jun  5 07:51:13 2016 Nicolas Chevalier
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

int	add_element_history(t_history *history, char *str)
{
  t_cmd	cmd;

  cmd.command = str;
  cmd.length = strlen(str);
  if(add_command(&history->commands, &cmd) == 1)
    return (1);
  history->current_cmd = history->commands.last;
  return (0);
}

char		*return_str(char *str, t_info *info, t_history *history)
{
  char		*s;
  int		fd;
  char		*clear;

  /* printf("%d", info->fd); */
  /* exit (0); */
  /* write(info->fd, info->keydown, my_strlen(info->keydown)); */
  /* clear = tigetstr("el"); */
  /* write(info->fd, clear, my_strlen(clear)); */
  /* write(info->fd, info->keydown, my_strlen(info->keydown)); */
  /* write(info->fd, info->keyup, my_strlen(info->keyup)); */
  /* close(info->fd); */
  if (str != NULL)
    {
      add_element_history(history, str);
      write_file(history);
    }
  my_putstr("\n");
  /* my_putstr("\n"); */
  return (str);
}

static int	check_key(char *buff)
{
  if (buff[0] != '\t' && buff[0] != '\n' && buff[0] != 127
      && buff[2] != LEFT && buff[2] != RIGHT
      && buff[2] != DOWN && buff[2] != UP
      && buff[0] != CLEAR)
    return (0);
  return (1);
}

static void	manage_line(t_edit *line, t_info *info,
			    char buff[10], t_history *history)
{
  /* printf("(%d)", info->term); */
  /* exit (0); */
  /* if (info->term == 1) */
  keyboard(line, buff, history);
  if (check_key(buff) == 0)
    {
      if (line->pos == 0)
	add_character_normal(line, buff[0]);
      else
	add_character_advanced(line, buff[0]);
    }
}

char		*get_line(t_history *history, t_info *info)
{
  t_edit	line;
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
      if (check_key(buff) == 0)
	my_putstr(buff);
      if (buff[0] == 4 && buff[1] == '\0')
	return (NULL);
      if (buff[0] == '\n')
	return (return_str(line.cmd, info, history));
      manage_line(&line, info, buff, history);
    }
  return (line.cmd);
}

/*
** history.c for keyboard.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:29:38 2016 Nicolas Chevalier
** Last update Fri Jun  3 23:14:01 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <curses.h>
#include <term.h>
#include "history.h"
#include "get_line.h"

static int	is_key(char *buff, int ESC, int HOOK, int KEY)
{
  if (buff[0] == ESC && buff[1] == HOOK && buff[2] == KEY)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

static int	history_func(t_edit *line, t_history *history, char *buff)
{
  char	*el;
  char	*home;
  char	*save;
  int	fd;

  fd = open("/dev/tty", O_RDWR);
  save = tigetstr("rc");
  home = tigetstr("cub1");
  el = tigetstr("el");
  if  (buff[2] == 'A' && history->current_cmd != NULL &&
       history->current_cmd->prev != NULL)
    {
      write(fd, save, my_strlen(save));
      write(fd, el, my_strlen(el));
      history->current_cmd = history->current_cmd->prev;
      my_putstr(history->current_cmd->command);
    }
  else if (buff[2] == 'B' && history->current_cmd != NULL &&
       history->current_cmd->next != NULL)
    {
      write(fd, save, my_strlen(save));
      write(fd, el, my_strlen(el));
      history->current_cmd = history->current_cmd->next;
      my_putstr(history->current_cmd->command);
    }
}

static char	*my_autocomplete(char *str)
{
  struct dirent	*dirent;
  DIR		*dir;

  if ((dir = opendir("./")) == NULL)
    {
      my_putstr("ERROR");
      exit(EXIT_FAILURE);
    }
  my_putstr("\n");
  while ((dirent = readdir(dir)))
    {
      if (dirent->d_name[0] != '.')
  	my_putstr(dirent->d_name);
      my_putstr(" ");
    }
  /* my_putstr("\n"); */
  /* return (str); */
}

int		keyboard(t_edit *line, char *buff, t_history *history)
{
  if (is_key(buff, 27, 91, UP) || is_key(buff, 27, 91, DOWN))
    history_func(line, history, buff);
  if (buff[0] == '\t')
    my_autocomplete(line->cmd);
}

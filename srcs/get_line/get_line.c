/*
** get_line.c for get_line.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:27:38 2016 Nicolas Chevalier
** Last update Sun Jun  5 23:04:24 2016 Paul Wery
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

static char	*return_str(char *str, t_history *history)
{
  mode(1, 0);
  if (str != NULL)
    {
      add_element_history(history, str);
      write_file(history);
    }
  my_putstr("\n");
  if (str == NULL)
    {
      str = realloc(str, 1);
      str[0] = '\0';
    }
  return (str);
}

static void	manage_line(t_edit *line, t_info *info,
			    char buff[10], t_history *history)
{
  if (info->term == 1)
    keyboard(line, buff, history, info);
  if (check_key(buff) == 0)
    {
      if (line->pos == 0)
	add_character_normal(line, buff[0]);
      else
	add_character_advanced(line, buff[0], info);
    }
}

char		*get_line(t_history *history, t_info *info, char **env)
{
  t_edit	line;
  char		buff[10];
  int		len;

  len = 1;
  if (isatty(0) == 0)
    return (get_next_line());
  init(&line, env);
  while (len > 0)
    {
      memset(buff, '\0', 9);
      if ((len = read(0, buff, 10)) == -1)
	return (NULL);
      buff[len] = '\0';
      if (check_key(buff) == 0)
	my_putstr(buff);
      if (buff[0] == CTRLD && buff[1] == '\0')
	return (ctrld_());
      if (buff[0] == CTRLL)
	clear_screen_(&line, info, env);
      if (buff[0] == '\n')
	return (return_str(line.cmd, history));
      manage_line(&line, info, buff, history);
    }
  return (NULL);
}

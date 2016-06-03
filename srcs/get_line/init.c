/*
** init.c for init.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:33:04 2016 Nicolas Chevalier
** Last update Fri Jun  3 21:43:49 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <curses.h>
#include "function.h"
#include "get_line.h"

static void	init_edit_line(t_info *info, char **env)
{
  char		bp[1024];

  if (tgetent(bp, my_getterm(env)) <= 0)
    exit(EXIT_FAILURE);
  info->keyleft = tigetstr("kcub1");
  info->keyright = tigetstr("kcuf1");
  info->keyup = tigetstr("kcuu1");
  info->keydown = tigetstr("kcud1");
}

char		*init(t_edit *line, t_info *info, char **env)
{
  char		*s;

  line->cmd = NULL;
  line->len = 0;
  mode(0, 0, 1);
  init_edit_line(info, env);
  write(1, "prompt$>", my_strlen("prompt$>"));
  if ((isatty(0)) == 0)
    {
      s = get_next_line();
      return (s);
    }
  return (NULL);
}

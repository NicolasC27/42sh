/*
** init_fct.c for init_fct.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 22:41:06 2016 Nicolas Chevalier
** Last update Sun Jun  5 03:08:58 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <ncurses.h>
#include <term.h>
#include "function.h"
#include "history.h"
#include "get_line.h"

static int	init_editline(t_info *info, char **env)
{
  char		bp[1024];

  if (tgetent(bp, my_getterm(env)) <= 0)
    return (EXIT_FAILURE);
  info->keyleft = tigetstr("kcub1");
  info->keyright = tigetstr("kcuf1");
  info->keyup = tigetstr("kcuu1");
  info->keydown = tigetstr("kcud1");
  info->pos_begin = tigetstr("sc");
  my_putstr(info->pos_begin);
  return (EXIT_SUCCESS);
}

void		init_fct(t_history *history,  char **env, t_info *info)
{
  init_editline(info, env);
  init_history(history);
}

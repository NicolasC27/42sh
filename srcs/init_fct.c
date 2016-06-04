/*
** init_fct.c for init_fct.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sat Jun  4 22:41:06 2016 Nicolas Chevalier
** Last update Sat Jun  4 22:47:35 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <curses.h>
#include "function.h"
#include "get_line.h"
#include "mins.h"

static void	init_editline(t_info *info, char **env)
{
  char		bp[1024];

  if (tgetent(bp, my_getterm(env)) <= 0)
    exit(EXIT_FAILURE);
  info->keyleft = tigetstr("kcub1");
  info->keyright = tigetstr("kcuf1");
  info->keyup = tigetstr("kcuu1");
  info->keydown = tigetstr("kcud1");
  info->pos_begin = tigetstr("sc");
  my_putstr(info->pos_begin);
}

void		init_fct(t_history *history, t_env *ev, char **env, t_info *info)
{
  init_editline(info, env);
  init_history(history);
  if (ini_env(ev) == -1
      || (ev->env = create_my_env(env, 0, 0, ev)) == NULL)
    return (0);
}

/*
** history.c for keyboard.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:29:38 2016 Nicolas Chevalier
** Last update Sun Jun  5 20:40:06 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "function.h"
#include "get_line.h"

static int	is_key(char *buff, int ESC, int HOOK, int KEY)
{
  if (buff[1] == '\0')
    return (1);
  if (buff[0] == ESC && buff[1] == HOOK && buff[2] == KEY)
    return (0);
  return (1);
}

static void	manage_control(t_edit *line, t_info *info, char *buff)
{
  if (buff[0] == CTRLA || (is_key(buff, 27, 79, HOME) == 0))
    control_a(line, info);
  if (buff[0] == CTRLK)
    control_k(line, info);
  if (buff[0] == CTRLE)
    control_e(line, info);
  if (is_key(&buff[3], 59, 53, LEFT) == 0)
    control_ctrlleft(line, info);
  if (is_key(&buff[3], 59, 53, RIGHT) == 0)
    control_ctrlright(line, info);
}

int		keyboard(t_edit *line, char *buff, t_history *history, t_info *info)
{
  if (is_key(buff, 27, 91, UP) == 0 || is_key(buff, 27, 91, DOWN) == 0)
    history_func(line, history, buff, info);
  else if (is_key(buff, 27, 91, LEFT) == 0)
    cursors_left(line, info);
  else if (is_key(buff, 27, 91, RIGHT) == 0)
    cursors_right(line, info);
  else if (buff[0] == '\t')
    my_autocomplete();
  else if (buff[0] == 127 || buff[0] == 8)
    cursors_delete(line, info);
  manage_control(line, info, buff);
  return (0);
}

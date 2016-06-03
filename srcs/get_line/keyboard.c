/*
** history.c for keyboard.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:29:38 2016 Nicolas Chevalier
** Last update Fri Jun  3 21:45:58 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include "get_line.h"

static void	history(t_edit *line)
{
}

static int	is_key(char *buff, int ESC, int HOOK, int KEY)
{
  if (buff[0] == ESC && buff[1] == HOOK && buff[2] == KEY)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);

}

int		keyboard(t_edit *line, char *buff)
{
  if (is_key(buff, 27, 91, UP) || is_key(buff, 27, 91, DOWN))
    history(line);
}

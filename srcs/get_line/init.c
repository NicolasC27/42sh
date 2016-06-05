/*
** init.c for init.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:33:04 2016 Nicolas Chevalier
** Last update Sun Jun  5 16:08:41 2016 Nicolas Chevalier
*/

#include <stdlib.h>
#include <curses.h>
#include "function.h"
#include "get_line.h"

char		*init(t_edit *line, char **env)
{
  line->cmd = NULL;
  line->len = 0;
  line->pos = 0;
  mode(0, 1);
  prompt(env);
  return (NULL);
}

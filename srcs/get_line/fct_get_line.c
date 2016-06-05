/*
** fct_get_line.c for fct_get_lin.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Jun  5 16:19:44 2016 Nicolas Chevalier
** Last update Sun Jun  5 16:22:03 2016 Nicolas Chevalier
*/

#include <ncurses.h>
#include "get_line.h"
#include "function.h"

void		clear_screen_(t_info *info, char **env)
{
  char		*s;

  s = tigetstr("clear");
  write(info->fd, s, my_strlen(s));
  prompt(env);
}

char		*ctrld_()
{
  mode(1, 0);
  my_putstr("\n");
  return (NULL);
}

int		check_key(char *buff)
{
  if (buff[0] != '\t' && buff[0] != '\n' && buff[0] != 127
      && buff[2] != LEFT && buff[2] != RIGHT
      && buff[2] != DOWN && buff[2] != UP
      && buff[0] != CLEAR && buff[2] != DELETE
      && buff[0] != CTRLK && buff[0] != CTRLA
      && buff[0] != CTRLD && buff[0] != CTRLE
      && buff[0] != CTRLL)
    return (0);
  return (1);
}

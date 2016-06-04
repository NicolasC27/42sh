/*
** canonical_mode.c for 42sh in /home/gerard_v/Documents/42sh/srcs
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "history.h"

void	canonical_mode(struct termios *oldt, struct termios *newt, int mode)
{
  if (mode == 0)
    {
      ioctl(0, TCGETS, oldt);
      newt = oldt;
      newt->c_lflag &= ~ECHO;
      newt->c_lflag &= ~ICANON;
      newt->c_cc[VMIN] = 1;
      newt->c_cc[VTIME] = 0;
      ioctl(0, TCSETS, newt);
    }
  else if (mode == 1)
    ioctl(0, TCSETS, oldt);
}

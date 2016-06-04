/*
** mode.c for mode.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:30:17 2016 Nicolas Chevalier
** Last update Sat Jun  4 22:15:12 2016 Nicolas Chevalier
*/

#include <sys/ioctl.h>
#include <termios.h>
#include <stdlib.h>
#include "get_line.h"

int			mode(int fd, int i, int option)
{
  static struct termios	oldT;
  static struct termios	newT;

  if (i == 0)
    {
      ioctl(fd, TCGETS, &oldT);
      ioctl(fd, TCGETS, &newT);

      newT.c_lflag &= ~ECHO;
      newT.c_lflag &= ~ICANON;
      if (option == 1)
	{
	  newT.c_cc[VMIN] = 1;
	  newT.c_cc[VTIME] = 0;
	}
      ioctl(fd, TCSETS, &newT);
    }
  if (i == 1)
    ioctl(fd, TCSETS, &oldT);
  return (0);
}

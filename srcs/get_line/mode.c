/*
** mode.c for mode.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Fri Jun  3 21:30:17 2016 Nicolas Chevalier
** Last update Sun Jun  5 13:29:49 2016 Nicolas Chevalier
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
      if (ioctl(0, TCGETS, &oldT) == -1)
	exit(EXIT_FAILURE);
      if (ioctl(0, TCGETS, &newT) == -1)
	exit(EXIT_FAILURE);
      newT.c_lflag &= ~ECHO;
      newT.c_lflag &= ~ICANON;
      if (option == 1)
	{
	  newT.c_cc[VMIN] = 1;
	  newT.c_cc[VTIME] = 0;
	}
      ioctl(0, TCSETS, &newT);
    }
  if (i == 1)
    if (ioctl(0, TCSETS, &oldT) == -1)
      exit(EXIT_FAILURE);
  return (0);
}

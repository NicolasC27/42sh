/*
** get_line.c for get_line.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:27:38 2016 Nicolas Chevalier
** Last update Tue May 31 12:52:31 2016 Nicolas Chevalier
*/

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <dirent.h>
#include "function.h"
#include "get_line.h"

static int		mode(int i, int option)
{
  static struct termios	oldT;
  static struct termios	newT;

  if (i == 0)
    {
      ioctl(0, TCGETS, &oldT);
      ioctl(0, TCGETS, &newT);

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
    ioctl(0, TCSETS, &oldT);
  return (0);
}

static char	*my_autocomplete(char *str)
{
  struct dirent	*dirent;
  DIR		*dir;

  if ((dir = opendir("./")) == NULL)
    {
      my_putstr("ERROR");
      exit(EXIT_FAILURE);
    }
  my_putstr("\n");
  while ((dirent = readdir(dir)))
    {
      if (dirent->d_name[0] != '.')
	my_putstr(dirent->d_name);
      my_putstr(" ");
    }
  return (str);
}

char		*get_line(void)
{
  char		*str;
  char		buff[8];
  int		len;
  int		i;

  len = 1;
  str = NULL;
  i = 0;
  mode(0,1);
  while (len > 0)
    {
      if ((len = read(0, buff, 9)) == -1)
	return (NULL);
      buff[len] = '\0';
      my_putstr(buff);
      if (buff[0] == '\t')
	return (my_autocomplete(str));
      str = realloc(str, i + 2);
      str[i] = buff[0];
      str[i + 1] = '\0';
      i += 1;
    }
  return (str);
}

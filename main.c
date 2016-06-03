/*
** main.c for main.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Jun  2 22:46:19 2016 Nicolas Chevalier
** Last update Thu Jun  2 23:00:03 2016 Nicolas Chevalier
*/

#include <termio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

static int		mode(int fd, int i, int option)
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
	  newT.c_cc[VMIN] = 0;
	  newT.c_cc[VTIME] = 1;
	}
      ioctl(fd, TCSETS, &newT);
    }
  if (i == 1)
    ioctl(fd, TCSETS, &oldT);
  return (0);
}

char		*my_getterm(char **env)
{
  int		i;
  int		j;

  i = 0;
  while (env[i])
    {
      j = -1;
      if (env[i][++j] == 'T')
	if (env[i][j + 1] == 'E' && env[i][j + 2] == 'R' && env[i][j + 3] == 'M'
	    && env[i][j + 4] == '=')
	  return (&env[i][j + 5]);
      i++;
    }
  return (NULL);
}

int		main(int argc, char **argv, char **env)
{
  int		len;
  char		bp[1024];
  char		buff[9];
  char		*s;

  mode(0, 0, 1);
  len = read(0, buff, 8);
  printf("%d %d %d", buff[0], buff[1], buff[2]);
  if (tgetent(bp, my_getterm(env)) <= 0)
    exit(EXIT_FAILURE);
  s = tigetstr("kcuu1");
  printf("\n%d %d %d", s[0], s[1], s[2]);
  mode(0, 1, 0);
}

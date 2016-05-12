/*
** get_next_line.c for g_n_l.c in /home/cheval_8/rendu/CPE_2014_get_next_line
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Nov 18 19:52:00 2014 Nicolas Chevalier
** Last update Sun Mar 20 04:15:38 2016 Chevalier Nicolas
*/

#include	"gnl.h"

int		read_gnl(int fd, int *len, int *i, char *buff)
{
  if ((*len) == (*i))
    {
      *(i) = 0;
      if (((*len) = read(fd, buff, BUFF_SIZE)) <= 0)
	return (0);
    }
  return (1);
}

char		*get_next_line(const int fd)
{
  static char	buff[BUFF_SIZE];
  static int	len;
  static int	a;
  char		*str;
  int		n;

  n = 0;
  if ((read_gnl(fd, &len, &a, buff)) == 0)
    return (NULL);
  if ((str = malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
    return (NULL);
  my_memset(str, 0, BUFF_SIZE + 1);
  while (buff[a] && buff[a] != '\n')
    {
      str[n++] = buff[a++];
      if (n >= BUFF_SIZE)
	str = my_realloc(str, 1);
      if ((read_gnl(fd, &len, &a, buff)) == 0)
	  return (str);
    }
  a++;
  str[n] = '\0';
  return (str);
}

/*
** get_next_line.c for get in /home/carbon_b/getnexline/CPE_2015_getnextline
**
** Made by Guillaume CARBONNIER
** Login   <carbon_b@epitech.net>
**
** Started on  Thu Jan 14 15:16:14 2016 Guillaume CARBONNIER
** Last update Sun Jun  5 04:13:33 2016 Nicolas Chevalier
*/

#include "mins.h"

char	*m_realloc(char *str, int size)
{
  char	*new;
  int	i;
  int	a;

  i = 0;
  a = 0;
  while (str[i] != '\0')
    ++i;
  if ((new = malloc(sizeof(char) * (i + size) + 1)) == NULL)
    return (NULL);
  while (a <= (i + size))
    new[a++] = '\0';
  i = 0;
  while (str[i] != '\0')
    {
      new[i] = str[i];
      ++i;
    }
  free(str);
  return (new);
}

char		reader(const int fd)
{
  static char	*str = NULL;
  static int	i = -1;
  static int	a = -1;

  if (fd == -1)
    return ('\0');
  if (a == i)
    {
      if (str != NULL)
	free(str);
      if ((str = malloc(sizeof(char) * READ_SIZ + 1)) == NULL)
	return ('\0');
      str[READ_SIZ] = '\0';
      i = read(fd, str, READ_SIZ);
      if (i == 0)
	{
	  free(str);
	  return ('\0');
	}
      a = 0;
    }
  if (i == 0)
    return ('\0');
  return (str[a++]);
}

static int	init(t_tmp *tempo)
{
  tempo->c = 0;
  if ((tempo->line = malloc(sizeof(char) * 1 + 1)) == NULL)
    return (1);
  tempo->line[1] = '\0';
  tempo->line[0] = '\0';
  return (0);
}

char	*get_file(const int fd)
{
  t_tmp	tempo;

  if (init(&tempo) == 1)
    return (NULL);
  while (tempo.c != '\n')
    {
      tempo.i = 0;
      tempo.c = reader(fd);
      if (tempo.c == '\0' && tempo.line[0] == '\0')
	{
	  free(tempo.line);
	  return (NULL);
	}
      if (tempo.c == '\0' && tempo.line[0] != '\0')
	tempo.c = '\n';
      if (tempo.c != '\n')
	{
	  if ((tempo.line = m_realloc(tempo.line, 1)) == NULL)
	    return (NULL);
	  while (tempo.line[tempo.i] != '\0')
	    ++tempo.i;
	  tempo.line[tempo.i] = tempo.c;
	}
    }
  return (tempo.line);
}

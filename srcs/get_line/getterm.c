/*
** getterm.c for getterm.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Jun  2 18:04:06 2016 Nicolas Chevalier
** Last update Sun Jun  5 08:10:15 2016 Nicolas Chevalier
*/

#include <stdio.h>
#include "get_line.h"

char		*my_gethome(char **env)
{
  int		i;
  int		j;

  i = 0;
  while (env[i])
    {
      j = -1;
      if (env[i][++j] == 'H')
	if (env[i][j + 1] == 'O' && env[i][j + 2] == 'M' && env[i][j + 3] == 'E'
	    && env[i][j + 4] == '=')
	  return (&env[i][j + 5]);
      i++;
    }
  return (NULL);
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

/*
** prompt.c for prompt.c in /home/cheval_8/rendu/PSU_2015_42sh
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Jun  5 08:44:47 2016 Nicolas Chevalier
** Last update Sun Jun  5 09:27:02 2016 Nicolas Chevalier
*/

#include <curses.h>
#include "get_line.h"

char		*my_getpwd(char **env)
{
  int		i;
  int		j;

  i = 0;
  while (env[i])
    {
      j = -1;
      if (env[i][++j] == 'P')
	if (env[i][j + 1] == 'W' && env[i][j + 2] == 'D' && env[i][j + 3] == '=')
	  return (&env[i][j + 4]);
      i++;
    }
  return (NULL);
}

char		*my_getuser(char **env)
{
  int		i;
  int		j;

  i = 0;
  while (env[i])
    {
      j = -1;
      if (env[i][++j] == 'U')
	if (env[i][j + 1] == 'S' && env[i][j + 2] == 'E' && env[i][j + 3] == 'R'
	    && env[i][j + 4] == '=')
	  return (&env[i][j + 5]);
      i++;
    }
  return (NULL);
}

int		prompt(char **env)
{
  char		*user;
  char		*pwd;
  char		*s;
  int		i;

  user = my_getuser(env);
  pwd = my_getpwd(env);
  if (user != NULL || pwd != NULL)
    {
      my_putstr(RED"(");
      if (user)
	my_putstr(user);
      if (pwd)
	{
	  my_putstr("@"CYAN);
	  my_putstr(pwd);
	}
      my_putstr(RED")");
    }
  my_putstr(RED"->"DEFAULT);
}

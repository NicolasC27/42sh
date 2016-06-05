/*
** my_cat.c for my_cat in /home/carbon-b/Rendu/PSU/42sh/the_last_project_of_the_world/the_last_project_of_the_world
** 
** Made by carbon_b
** Login   <carbon_b@epitech.net>
** 
** Started on  Fri Jun  3 15:28:07 2016 carbon_b
** Last update Sat Jun  4 17:05:28 2016 carbon_b
*/

#include "mins.h"

int	last_char(char *s1, int a, int bool)
{
  if (bool == 0)
    {
      if (s1[a - 1] >= 'a' && s1[a - 1] <= 'z')
      	return (1);
      else if (s1[a - 1] >= 'A' && s1[a - 1] <= 'Z')
      	return (1);
    }
  else
    {
      if (s1[a + 1] >= 'a' && s1[a + 1] <= 'z')
	return (1);
      else if (s1[a + 1] >= 'A' && s1[a + 1] <= 'Z')
	return (1);
    }
  return (0);
}

char	*my_cat(char *buff, char *cmd, char *alias)
{
  char	*r_cmd;
  int	nb;
  int	pos;

  if ((pos = check(buff, alias)) == -1)
    return (buff);
  nb = (strlen(buff) - strlen(alias)) + strlen(cmd);
  r_cmd = malloc(nb + 1);
  if (r_cmd == NULL)
    return (NULL);
  memset(r_cmd, '\0', nb + 1);
  if (pos > 0)
    {
      strncpy(r_cmd, buff, pos);
      strcat(r_cmd, cmd);
    }
  else
    strncpy(r_cmd, cmd, strlen(cmd));
  strcat(r_cmd, &buff[pos + strlen(alias)]);
  free(buff);
  return (r_cmd);
}

/*
** my_str.c for my_str.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Jan 14 03:41:47 2016 Nicolas Chevalier
** Last update Sat Jan 23 22:01:32 2016 Nicolas Chevalier
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int		my_strlen(char *str)
{
  int		i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] && str[i] != '\0')
    i++;
  return (i);
}

char		my_strcmp(char *s1, char *s2, int len)
{
  int		i;

  i = -1;
  while (s1[++i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]);
  if (len == 1)
    return (s1[i] == '=' && s2[i] == '\0');
  return ((s1[i] == s2[i] || s1[i] == ' ' || s1[i] == '\t') && s2[i] == '\0');
}

char		*my_strdup(char *str)
{
  int	       i;
  char		*str2;

  if (str == NULL)
    return (NULL);
  if ((str2 = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    my_putstr("Error with a memory allocation(1)");
  i = -1;
  while (str[++i] != '\0')
    str2[i] = str[i];
  str2[i] = '\0';
  return (str2);
}

char		*my_strcat(char *path, char *command, int cond)
{
  char		*tab;
  int		i;
  int		j;

  if (path == NULL || command == NULL)
    return (NULL);
  if ((tab = malloc(sizeof(char) * (my_strlen(path) +
				    my_strlen(command) + 2))) == NULL)
    my_puterror("Error with a memory allocation");
  i = -1;
  while (path[++i] != '\0')
    tab[i] = path[i];
  if (cond == 1)
    tab[i++] = '/';
  if (cond == 2)
    tab[i++] = '=';
  j = 0;
  while (command[j] != '\0')
    tab[i++] = command[j++];
  tab[i] = '\0';
  return (tab);
}

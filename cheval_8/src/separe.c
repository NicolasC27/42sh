/*
** my_str_to_wordtab.c for my_str_to_wordtab.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Wed Jan  6 23:20:40 2016 Nicolas Chevalier
** Last update Thu Apr 14 22:38:01 2016 Chevalier Nicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

static int		my_count(char *str, char c, int k)
{
  int			i;
  int			count;

  i = 0;
  count = 0;
  while (str[i])
    {
      while (str[i] && (str[i] == c || str[i] == k || str[i] == '\t'))
	i++;
      count += (str[i]) ? (1) : (0);
      i += (str[i]) ? (1) : (0);
    }
  return (count);
}

static char		*return_tab(char *str, int count)
{
  char			*tab;
  int			i;
  int			size;

  size = count;
  while (str[size - 1] == ' ' || str[size - 1] == '\t')
    size -= 1;
  if ((tab = malloc(sizeof(char) * size + 1)) == NULL)
    return (NULL);
  i = -1;
  while (str[++i] && i < size)
    tab[i] = str[i];
  tab[i] = '\0';
  return (tab);
}

static char		*get_str(char *str, int *i, char c, char k)
{
  int			size;
  int			j;
  int			len;

  len = 0;
  j = -1;
  size = 0;
  while (str[++j] == c || str[j] == k)
    len += 1;
  j = 0;
  while (str[j] && ((str[j] != c && str[j] != k)))
    {
      size += 1;
      j += 1;
      (*i)++;
    }
  while (len-- > 0)
    {
      (*i)++;
      size += 1;
    }
  (*i)--;
  return (return_tab(str, size));
}

char			**separe_wordtab(char *str, char c)
{
  char			**tab;
  int			i;
  int			z;

  i = 0;
  z = -1;
  if ((tab = malloc((my_count(str, c, '\0') + 1) * sizeof(*tab))) == NULL)
    my_puterror("Problem with a memory allocation(2)");
  while (str[i])
    {
      while (str[i] && (str[i] == c || str[i] == ' ' || str[i] == '\t'))
	i += 1;
      tab[++z] = (str[i]) ? get_str(&str[i], &i, c, 12) : '\0';
      i += (str[i]) ? (1) : (0);
    }
  tab[z + 1] = '\0';
  return (tab);
}

char			**separe_redirection(char **str)
{
  char			**tab;
  int			i;
  int			z;
  int			j;

  j = 0;
  z = -1;
  if ((tab = malloc(100 + my_count(str[j], '>', '<') * sizeof(*tab))) == NULL)
    my_puterror("Problem with a memory allocation(2)");
  while (str[j])
    {
      i = 0;
      while (str[j][i])
	{
	  while (str[j][i] && (str[j][i] == ' ' || str[j][i] == '\t'))
	    i += 1;
	  tab[++z] = (str[j][i]) ? get_str(&(str[j][i]), &i, '>', '<') : '\0';
	  i += (str[j][i]) ? (1) : (0);
	}
      tab[z + 1] = '\0';
      j += 1;
    }
  return (tab);
}

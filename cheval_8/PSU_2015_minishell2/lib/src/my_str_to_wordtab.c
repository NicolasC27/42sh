/*
** my_str_to_wordtab.c for my_str_to_wordtab.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Wed Jan  6 23:20:40 2016 Nicolas Chevalier
** Last update Sat Apr  2 22:27:59 2016 Chevalier Nicolas
*/

#include "lib.h"

int		my_count(char *str, char c)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (str[i])
    {
      while (str[i] && (str[i] == c || str[i] == '\t'))
	i++;
      if (str[i])
	count++;
      if (str[i] != '\0')
	i++;
    }
  return (count);
}

int		my_strlentab(const char *str, char c)
{
  int		i;

  i = -1;
  while (str[++i] != '\0' && str[i] != c && str[i] != '\t');
  return (i);
}

char		**my_str_to_wordtab(char *str, char c)
{
  char		**tab;
  int		i;
  int		z;
  int		j;

  i = 0;
  z = -1;
  if ((tab = malloc((my_count(str, c) + 1) * sizeof(*tab))) == NULL)
    return (NULL);
  while (str[i])
    {
      j = 0;
      while (str[i] && (str[i] == c || str[i] == ' ' || str[i] == '\t'))
	++i;
      if ((tab[++z] = malloc((my_strlentab(&str[i], c) + 1)
			     * sizeof(**tab))) == NULL)
	return (NULL);
      while (str[i] && str[i] != c && str[i] != ' ' && str[i] != '\t')
	  tab[z][j++] = str[i++];
      tab[z][j] = '\0';
     while (str[i] && (str[i] == c || str[i] == ' ' || str[i] == '\t'))
	++i;
    }
  tab[z + 1] = '\0';
  return (tab);
}

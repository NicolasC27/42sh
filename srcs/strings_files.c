/*
** strings_files.c for strings_files in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sun Jan 17 03:46:45 2016 Paul Wery
** Last update Thu Jun  2 01:53:22 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	nb_opts(char *str, int n, int i)
{
  inhib(str, 0, 1);
  while (str[n] != '\0')
    {
      while (str[n] != '\0' && (str[n] == ' ' || str[n] == '\t'))
	n += 1;
      if (str[n] == '\0')
	return (i + 1);
      while (str[n] != '\0'
	     && (inhib(str, n, 0) == 1
		 || ((str[n] != ' ' || (n > 0 && str[n - 1] == '\\'))
		     && str[n] != '\t')))
	n += 1;
      i += 1;
    }
  return (i + 1);
}

int	ret_curs(int n, char *str)
{
  inhib(str, 0, 1);
  while (str[n] != '\0'
	 && (inhib(str, n, 0) == 1
	     || ((str[n] != ' ' || (n > 0 && str[n - 1] == '\\'))
		 && str[n] != '\t')))
    n += 1;
  return (n);
}

char	*build_opts(char *str, int n)
{
  char	*opt;
  int	size;
  int	i;

  i = 0;
  size = ret_curs(n, str) - n + 1;
  if ((opt = malloc(size)) == NULL)
    return (NULL);
  size = n;
  not_inhib(str, 0, 1);
  while (size < ret_curs(n, str))
    {
      if ((not_inhib(str, size, 0) == 0 && str[size] != '\\'
	   && str[size] != '"' && str[size] != '\'')
	  || (not_inhib(str, size, 2) == 1 && str[size] != '"')
	  || (not_inhib(str, size, 2) == 2 && str[size] != '\''))
	opt[i++] = str[size++];
      else
	size += 1;
    }
  opt[i] = '\0';
  return (opt);
}

char	**get_opts(char *str, int n, int z)
{
  char	**opts;

  if ((opts = malloc((nb_opts(str, 0, 0)) * sizeof(char*))) == NULL)
    return (NULL);
  while (str[n] != '\0')
    {
      while ((str[n] == ' ' || str[n] == '\t') && str[n] != '\0')
	n += 1;
      if (str[n] != '\0')
	{
	  if ((opts[z] = build_opts(str, n)) == NULL)
	    return (NULL);
	  n = ret_curs(n, str);
	  z += 1;
	}
    }
  opts[z] = NULL;
  return (opts);
}

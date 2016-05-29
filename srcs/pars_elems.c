/*
** pars_elems.c for pars_elems in /home/wery_p/rendu/build_42sh/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Wed May 25 16:35:51 2016 Paul Wery
** Last update Sun May 29 17:43:10 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>

int	new_elem(char *buffer, int n, char *ref)
{
  int	i;
  int	save_n;
  int	size;

  i = 0;
  save_n = n;
  while (ref[i] != '\0')
    {
      size = 0;
      while (ref[i] == buffer[n] && buffer[n] != '\0'
	     && ref[i] != '\0' && ref[i] != ',')
	{
	  i += 1;
	  n += 1;
	  size += 1;
	}
      if (ref[i] == ',' || ref[i] == '\0')
	return (size);
      while (ref[i] != ',' && ref[i] != '\0')
	i += 1;
      if (ref[i] != '\0')
	i += 1;
      n = save_n;
    }
  return (0);
}

int	get_nb_elems(char *buffer, char *ref, int n, int size)
{
  int	add;
  int	elem;

  while (buffer[n] != '\0')
    {
      elem = 0;
      while (buffer[n] != '\0' && (buffer[n] == ' ' || buffer[n] == '\t'))
	n += 1;
      while (buffer[n] != '\0' && (add = new_elem(buffer, n, ref)) == 0)
	{
	  n += 1;
	  elem = 1;
	}
      n += add;
      if (elem == 1)
	size += 1;
      if (add != 0)
	size += 1;
      while (buffer[n] != '\0' && (buffer[n] == ' ' || buffer[n] == '\t'))
	n += 1;
    }
  return (size);
}

char	*parsed_elem(char *buffer, int n, char *ref)
{
  char	*elem;
  int	i;
  int	size;

  size = n;
  i = 0;
  if (new_elem(buffer, n, ref) == 0)
    {
      while (buffer[size] != '\0' && new_elem(buffer, size, ref) == 0)
	size += 1;
    }
  else
    size = n + new_elem(buffer, n, ref);
  if ((elem = malloc(size - n + 1)) == NULL)
    return (NULL);
  while (n < size)
    elem[i++] = buffer[n++];
  elem[i] = '\0';
  return (elem);
}

int	new_pos(char *buffer, int i)
{
  if (new_elem(buffer, i, "<<,>>,||,&&,<,>,|,&,;") == 0)
    {
      while (new_elem(buffer, i, "<<,>>,||,&&,<,>,|,&,;") == 0
	     && buffer[i] != '\0')
	i += 1;
    }
  else
    i += new_elem(buffer, i, "<<,>>,||,&&,<,>,|,&,;");
  return (i);
}

char	**pars_elems(char *buffer)
{
  char	**pars;
  int	size;
  int	n;
  int	i;

  n = 0;
  i = 0;
  size = get_nb_elems(buffer, "<<,>>,||,&&,<,>,|,&,;", 0, 0);
  if ((pars = malloc(sizeof(char*) * (size + 1))) == NULL)
    return (NULL);
  while (n < size)
    {
      while (buffer[i] != '\0' && (buffer[i] == ' ' || buffer[i] == '\t'))
	i += 1;
      if ((pars[n++] = parsed_elem(buffer, i,
				   "<<,>>,||,&&,<,>,|,&,;")) == NULL)
	return (NULL);
      i = new_pos(buffer, i);
    }
  pars[n] = NULL;
  return (pars);
}

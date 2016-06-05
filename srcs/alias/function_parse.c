/*
** function_parse.c for function in /home/carbon-b/Rendu/PSU/42sh/the_last_project_of_the_world
** 
** Made by carbon_b
** Login   <carbon_b@epitech.net>
** 
** Started on  Tue May 31 15:30:21 2016 carbon_b
** Last update Sat Jun  4 14:34:40 2016 carbon_b
*/

#include "mins.h"

int		check(char *s1, char *s2)
{
  size_t	a;
  size_t	b;

  a = 0;
  b = 0;
  while (s1[a])
    {
      if (s1[a] == s2[b])
	{
	  if ((b == 0 && a > 0 && last_char(s1, a, 0) == 1)
	      || ((b == strlen(s2) - 1) && (a < strlen(s1) - 1)
		  && last_char(s1, a, 1) == 1))
	    b = 0;
	  else
	    b++;
	}
      else if (s1[a] != s2[b])
	b = 0;
      if (s2[b] == '\0')
	return (a - strlen(s2) + 1);
      a++;
    }
  return (-1);
}

int		create_node(t_list *list, t_alias *alias)
{
  t_node	*new;
  t_node	*tmp;

  if (!alias->name || !alias->cmd)
    return (-1);
  if ((new = malloc(sizeof(t_node))) == NULL)
    return (-1);
  new->next = NULL;
  new->alias = strdup(alias->name);
  new->cmd = strdup(alias->cmd);
  if (list->size == 0)
    {
      list->first = new;
      list->size++;
    }
  else if (list->size > 0)
    {
      tmp = list->first;
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;
      list->size++;
    }
  return (0);
}

char	*get_cmd(char *line)
{
  int	start;
  int	end;
  int	i;
  char	*res;

  start = -1;
  i = -1;
  while (line[++start] != '\'' && line[start] != '\0');
  if (line[start] == '\0')
    return (NULL);
  end = ++start;
  while (line[++end] != '\'' && line[end] != '\0');
  if ((res = malloc(sizeof(char) * (end - start + 1))) == NULL)
    return (NULL);
  res[end - start] = 0;
  while (start < end)
    {
      res[++i] = line[start];
      ++start;
    }
  return (res);
}

char	*get_name(char *line)
{
  int	start;
  int	end;
  int	i;
  char	*res;

  start = -1;
  i = 0;
  if (!line)
    return (NULL);
  while (line[++start] != ' ' && line[start] != '\0');
  if (line[start] == 0)
    return (NULL);
  end = ++start;
  while (line[++end] != '=' && line[end] != '\0');
  if (line[start] == 0)
    return (NULL);
  if ((res = malloc(sizeof(char) * (end - start + 1))) == NULL)
    return (NULL);
  res[end - start] = 0;
  while (start < end)
    {
      res[i++] = line[start];
      ++start;
    }
  return (res);
}

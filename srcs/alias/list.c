/*
** parse.c for parse in /home/carbon-b/Rendu/PSU/42sh/the_last_project_of_the_world
**
** Made by carbon_b
** Login   <carbon_b@epitech.net>
**
** Started on  Tue May 31 13:48:04 2016 carbon_b
** Last update Sun Jun  5 20:01:40 2016 Paul Wery
*/

#include "mins.h"

char		*alias_check(char *str, t_list *list)
{
  t_node	*tmp;
  int		pos;
  char		*final;
  int		alias;

  tmp = list->first;
  final = strdup(str);
  while (tmp != NULL)
    {
      alias = 0;
      pos = 0;
      while (pos != -1)
	{
	  if ((pos = check(final, tmp->alias)) >= 0)
	    final = my_cat(final, tmp->cmd, tmp->alias);
	  alias++;
	  if (alias >= 10)
	    pos = -1;
	}
      tmp = tmp->next;
    }
  return (final);
}

void	parse_line(t_alias *alias, char *line)
{
  alias->name = get_name(line);
  alias->cmd = get_cmd(line);
}

void		free_list(t_list *list)
{
  t_node	*node_tmp;
  t_node	*node_tmp2;

  node_tmp = list->first;
  while (node_tmp)
    {
      node_tmp2 = node_tmp;
      node_tmp = node_tmp->next;
      free(node_tmp2->alias);
      free(node_tmp2->cmd);
      free(node_tmp2);
    }
  free(node_tmp);
}

void		c_list(t_list *list, char *line)
{
  t_alias	alias;

  alias.name = NULL;
  alias.cmd = NULL;
  parse_line(&alias, line);
  if (check(line, "alias") >= 0)
    create_node(list, &alias);
  if (alias.name)
    free(alias.name);
  if (alias.cmd)
    free(alias.cmd);
}

int		fill_list(t_list *list)
{
  int		fd;
  char		*str;

  list->size = 0;
  list->first = NULL;
  if ((fd = open(".42shrc", O_RDONLY)) == -1)
    {
      if ((fd = open(".42shrc", O_CREAT, 0664)) == -1)
	return (1);
      else
	return (0);
    }
  while ((str = get_file(fd)) != NULL)
    {
      c_list(list, str);
      if (str)
	free(str);
    }
  close(fd);
  return (0);
}

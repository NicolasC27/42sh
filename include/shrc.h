/*
** 42shrc.h for 42 in /home/carbon-b/Rendu/PSU/42sh/the_last_project_of_the_world
**
** Made by carbon_b
** Login   <carbon_b@epitech.net>
**
** Started on  Tue May 31 13:50:09 2016 carbon_b
** Last update Sun Jun  5 07:30:25 2016 Nicolas Chevalier
*/

#ifndef SHRC_H_
# define SHRC_H_

# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "get_file.h"

typedef	struct	s_node
{
  char		*alias;
  char		*cmd;
  struct s_node	*next;
}		t_node;

typedef	struct	s_list
{
  int		size;
  t_node	*first;
}		t_list;

typedef	struct	s_alias
{
  int		is;
  char		*name;
  char		*cmd;
}		t_alias;

/*
** my_cat.c
*/
int	last_char(char *s1, int a, int);
char	*my_cat(char *buff, char *cmd, char *alias);

/*
** parse_function.c
*/
int	create_node(t_list *list, t_alias *alias);
char	*get_name(char *line);
char	*get_cmd(char *line);
int	check(char *s1, char *s2);

/*
** list.c
*/
void	parse_line(t_alias *alias, char *line);
void	c_list(t_list *list, char *line);
int	fill_list(t_list *list);
void   	free_list(t_list *list);
char	*my_cat(char *buff, char *cmd, char *alias);
char	*alias_check(char *str, t_list *list);

#endif /* !SHRC_H_ */

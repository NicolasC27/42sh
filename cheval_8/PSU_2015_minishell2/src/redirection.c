/*
** redirection.c for redirection.c in /home/cheval_8/rendu/PSU_2015_minishell2/src
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Apr 10 06:50:52 2016 Chevalier Nicolas
** Last update Fri Apr 15 01:11:31 2016 Chevalier Nicolas
*/

#include "my.h"

void		check_options_end(char **tmp, int h, int *y, t_command **command)
{
  int		j;

  j = 0;
  if (tmp[h + 2] && tmp[h + 2][j] != '<' && tmp[h + 2][j] != '>')
    h += 2;
  if (tmp[h][j] != '\0' && tmp[h][j] != '>' && tmp[h][j] != '<')
    while (tmp[h])
      {
	j = 0;
	if (((*command)->data[(*y)] = malloc(sizeof(char) * 30)) == NULL)
	  exit (0);
	while (tmp[h][j] != '\0')
	  {
	    (*command)->data[(*y)][j] = tmp[h][j];
	    j += 1;
	  }
	(*command)->data[(*y)][j] = '\0';
	(*y) += 1;
	h += 1;
      }
}

static void	redirect(t_command **command, char **tmp, int i, int z)
{
  int		y;
  int		h;

  if (((*command)->redirection[z] = (t_redirection *)malloc(
							    sizeof(t_redirection))) == NULL)
    exit (0);
  init_struct_redirection(command, z);
  (*command)->nb_redirection += 1;
  if (tmp[i + 1])
    (*command)->redirection[z]->tab = separe_wordtab(tmp[i + 1], ' ');
  y = -1;
  while ((*command)->data[++y])
    (*command)->data[y] = '\0';
  h = 0;
  y = 0;
  while (tmp[h][0] != '>' && tmp[h][0] != '<')
    {
      (*command)->data[y] = tmp[h];
      y += 1;
      h += 1;
    }
  check_options_end(tmp, h, &y, command);
  (*command)->data[y] = '\0';
}

char		*loop_condition(t_command **command, char **tmp, int i, int *z)
{
  if ((tmp[i][0] == '>' || tmp[i][0] == '<'))
    {
      redirect(command, tmp, i, *z);
      (*z) += 1;
      (tmp[i][0] == '>' && tmp[i][1] == '>')
	? ((*command)->redirection[*z - 1]->redi_two_right = 1) :
	(tmp[i][0] == '<' && tmp[i][1] == '<')
	? ((*command)->redirection[*z - 1]->redi_two_left = 1) :
	(tmp[i][0] == '>' && tmp[i][1] != '>')
	? ((*command)->redirection[*z - 1]->redi_right = 1) :
	(tmp[i][0] == '<' && tmp[i][1] != '<')
	? ((*command)->redirection[*z - 1]->redi_left = 1) :
	(0);
    }
  return (0);
}

char		*check_redirection(t_command **command, char **tmp)
{
  int		i;
  int		z;

  z = 0;
  i = -1;
  if (((*command)->redirection = (t_redirection **)malloc(
							  sizeof(t_redirection *) * 20)) == NULL)
    exit (0);
  while (tmp[++i])
    loop_condition(command, tmp, i, &z);
  return (0);
}

char		*redirection_in_list(t_command **command)
{
  char		*error;
  char		**tmp;
  int		i;
  int		count;

  while ((*command) != NULL)
    {
      count = 0;
      i = -1;
      tmp = separe_redirection((*command)->data);
      (*command)->nb_redirection = 0;
      (*command)->redirection = NULL;
      while (tmp[++i])
	count += (tmp[i][0] == '>' || tmp[i][0] == '<') ? 1 : 0;
      if ((tmp[i - 1][0] == '>' || tmp[i - 1][0] == '<'))
	return ("Missing name for redirect\n");
      if (count > 0)
	if ((error = check_redirection(command, tmp)) != 0)
	  return (error);
      (*command) = (*command)->next;
    }
  return (0);
}

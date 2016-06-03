/*
** my_list.c for my_list in /home/wery_p/rendu/PSU_2015_minishell2/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Apr  2 01:20:11 2016 Paul Wery
<<<<<<< HEAD
** Last update Tue May 31 12:36:09 2016 Nicolas Chevalier
=======
** Last update Fri Jun  3 04:28:42 2016 Paul Wery
>>>>>>> master
*/

#include <stdlib.h>
#include <unistd.h>
#include "function.h"
#include "mins.h"

int	valid_command(t_exec *list)
{
  int	num;

  num = elem_redirection(list->next->tab[0], "<<,>>,||,&&,<,>,|,&,;");
  if (num == 1 || num == 2 || num == 3 || num == 5 || num == 6 || num == 7)
    {
      my_put_error("Invalid null command.\n");
      return (-1);
    }
  return (0);
}

void		empty_list(t_exec *root)
{
  t_exec	*it;
  t_exec	*save;

  it = root->next;
  while (it != root)
    {
      save = it->next;
      free_opts(it->tab);
      free(it);
      it = save;
    }
}

void	delete_list(t_exec **root)
{
  empty_list(*root);
  free(*root);
  *root = NULL;
}

int		add_elem_prev(t_exec *elem, char **tab,
			      int error, int error_two)
{
  t_exec	*new_elem;

  if ((new_elem = malloc(sizeof(*new_elem))) == NULL)
    return (-1);
  new_elem->tab = tab;
  new_elem->error = error + error_two;
  new_elem->next = elem;
  new_elem->prev = elem->prev;
  elem->prev->next = new_elem;
  elem->prev = new_elem;
  return (0);
}

t_exec		*create_list(void)
{
  t_exec	*root;

  if ((root = malloc(sizeof(*root))) == NULL)
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

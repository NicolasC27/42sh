/*
** parsing_error.c for parsing_errror in /home/wery_p/rendu/PSU_2015_42sh/srcs
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jun  4 17:26:47 2016 Paul Wery
** Last update Sat Jun  4 20:19:41 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int		parsing_error(t_exec *list)
{
  t_exec	*it;

  it = list->next;
  while (it != list)
    {
      if (it->tab[0] == NULL)
	{
	  my_put_error("Bad command line\n");
	  return (1);
	}
      it = it->next;
    }
  return (0);
}

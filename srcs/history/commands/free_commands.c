/*
** free_commands.c for 42sh in /home/gerard_v/Documents/42sh/srcs/commands
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "history.h"

void   	free_commands(t_commands *commands)
{
  t_cmd	*tmp1;
  t_cmd	*tmp2;

  tmp1 = commands->first;
  while (tmp1)
    {
      tmp2 = tmp1;
      tmp1 = tmp1->next;
      free(tmp2->command);
      free(tmp2);
    }
}

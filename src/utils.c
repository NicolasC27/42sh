/*
** utils.c for utils.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Jan  5 18:11:50 2016 Nicolas Chevalier
** Last update Sat Apr  2 19:53:44 2016 Chevalier Nicolas
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

void		my_putchar_err(char c)
{
  write(2, &c, 1);
}

void		my_putstr_err(char *str)
{
  int		i;

  i = -1;
  while (str && str[++i] != '\0')
    my_putchar_err(str[i]);
}

int		count_list(t_env *tmp, t_env *env)
{
  int		count;

  count = 0;
  while (tmp != env)
    {
      ++count;
      tmp = tmp->next;
    }
  return (count);
}

/*
** my_free.c for my_free.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Jan 24 23:25:15 2016 Nicolas Chevalier
** Last update Sun Jan 24 23:27:58 2016 Nicolas Chevalier
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

void		my_free(char **tab)
{
  int		i;

  i = 0;
  if (tab != NULL)
    {
      while (tab[i] != '\0')
      	free(tab[i++]);
      free(tab);
    }
}

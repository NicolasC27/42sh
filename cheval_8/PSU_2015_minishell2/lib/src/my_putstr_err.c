/*
** my_putstr_err.c for my_putstr_err.c in /home/cheval_8/rendu/PSU_2015_minishell2/lib/src
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Sun Apr 10 03:43:45 2016 Chevalier Nicolas
** Last update Sun Apr 10 03:47:09 2016 Chevalier Nicolas
*/

#include "lib.h"

void	my_putstr_err(char *str)
{
  if (write(2, str, my_strlen(str)) == -1)
      exit (1);
}

/*
** my_exit.c for my_exit in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Thu Jan 21 18:44:21 2016 Paul Wery
** Last update Sat May 28 23:37:48 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>
#include "mins.h"

int	act_place(char *word1, int i)
{
  while ((word1[i] == ' ' || word1[i] == '\t') && word1[i] != '\0')
    i += 1;
  return (i);
}

int	check_end_word(char *w1, int i)
{
  int	n;

  n = i;
  if (w1[i] == ' ' || w1[i] == '\t')
    while (w1[i] == ' ' || w1[i] == '\t')
      i += 1;
  if (w1[n] == ' ' || w1[n] == '\t')
    {
      if (w1[i] == '-')
	i += 1;
      while (w1[i] > 47 && w1[i] < 58)
	i += 1;
    }
  while (w1[i] == ' ' || w1[i] == '\t')
    i += 1;
  return (i);
}

int	get_val_return(char *word1, int i)
{
  int	status;
  int	sign;

  sign = 0;
  status = 0;
  i = act_place(word1, i);
  if (word1[i] == '-')
    {
      i = i + 1;
      sign = 1;
    }
  while (word1[i] != '\0' && word1[i] > 47 && word1[i] < 58)
    {
      status = (status * 10) + (word1[i] - 48);
      i = i + 1;
    }
  if (sign == 1)
    status = status * -1;
  return (status);
}

void	free_all(t_env *ev, char *buffer, int status UNUSED)
{
  if (buffer != NULL)
    free(buffer);
  free_opts(ev->env);
  free(ev->oldpwd);
  exit(status);
}

void	my_exit(char *w1, char *word2, char *buffer, t_env *ev)
{
  int	n;
  int	i;
  int	status;

  n = 0;
  i = 0;
  if (w1 == NULL)
    return ;
  while (w1[i] == ' ' || w1[i] == '\t')
    i += 1;
  while (w1[i] != '\0' && word2[n] != '\0' && w1[i] == word2[n])
    {
      i += 1;
      n += 1;
    }
  status = get_val_return(w1, i);
  i = check_end_word(w1, i);
  if (n == my_strlen(word2) && w1[i] == '\0')
    free_all(ev, buffer, status);
}

/*
** utils_env.c for utils_env.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Wed Jan 13 22:51:01 2016 Nicolas Chevalier
** Last update Sat Apr  2 19:59:37 2016 Chevalier Nicolas
*/

#include <stdlib.h>
#include "my.h"

char		*search_env(t_env *env, char *str)
{
  t_env		*tmp;
  int		i;

  if (env->prev->data == NULL)
    return (NULL);
  tmp = env->next;
  while (tmp != env)
    {
      i = 0;
      while (str[i] == tmp->data[i])
	{
	  i++;
	  if (tmp->data[i] == '=' && (my_strlen(str) == i))
	    return (&tmp->data[i + 1]);
	}
      tmp = tmp->next;
    }
  return (NULL);
}

t_env		*update_env(t_env *env, char *dir, char *str)
{
  t_env	*tmp;
  int		i;
  int		z;

  z = 0;
  tmp = env->next;
  while (tmp != env)
    {
      i = 0;
      while (tmp->data[i] == str[i])
	++i;
      if (tmp->data[i] == '=')
	{
	  i = 0;
	  if ((tmp->data = malloc(sizeof(char) * my_strlen(dir) + 2)) == NULL)
	    my_puterror("Error with a memory allocation\n");
	  while (dir[z] != '\0')
	    tmp->data[i++] = dir[z++];
	  tmp->data[i] = '\0';
	}
      tmp = tmp->next;
    }
  return (tmp);
}

char		**conv_list(t_env *env)
{
  t_env		*tmp;
  char		**tab;
  int		i;

  if (env->prev->data == NULL)
    return (NULL);
  tmp = env->next;
  if ((tab = malloc(sizeof(char *) * (count_list(tmp, env) + 1))) == NULL)
    my_puterror("Error with a memory allocation\n");
  i = -1;
  while (tmp != env)
    {
      tab[++i] = my_strdup(tmp->data);
      tmp = tmp->next;
    }
  tab[i] = '\0';
  return (tab);
}

void		display_env(t_env *env)
{
  t_env		*tmp;

  tmp = env->next;
  while (tmp != env)
    {
      my_putstr(tmp->data);
      my_putstr("\n");
      tmp = tmp->next;
    }
}

void		remove_env(t_env *env, char *command)
{
  t_env		*tmp;

  tmp = env->next;
  while (tmp != env && !my_strcmp(tmp->data, command, 1))
    tmp = tmp->next;
  if (tmp != env)
    {
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      free(tmp->data);
      free(tmp);
    }
}

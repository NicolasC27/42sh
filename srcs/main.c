/*
** main.c for main in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jan 16 20:40:01 2016 Paul Wery
** Last update Sun Jun  5 00:43:04 2016 Nicolas Chevalier
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_line.h"
#include "function.h"
#include "history.h"
#include "mins.h"

void	free_opts(char **opts)
{
  int	n;

  n = 0;
  while (opts[n] != NULL)
    free(opts[n++]);
  free(opts);
}

char		**next_step(char *buffer, t_env *ev)
{
  ev->free.buffer = buffer;
  if (pair(buffer, 0, 0, 0) == -1)
    {
      ev->val_exit = 1;
      return (ev->env);
    }
  else
    {
      if ((ev->free.pars = pars_elems(buffer)) == NULL
	  || (ev->free.list = create_list()) == NULL
	  || full_list(ev->free.list, ev->free.pars, ev) == -1)
	return (NULL);
      if (parsing_error(ev->free.list) == 0
	  && ((ev->env = exec_list(ev->free.list, ev, 0, 0)) == NULL
	      || default_io(ev->stdin, ev->stdout, 3) == -1))
	return (NULL);
      free_opts(ev->free.pars);
      delete_list(&ev->free.list);
    }
  return (ev->env);
}

int	comp_builtins(char *word1, char *word2)
{
  int	n;
  int	i;

  n = 0;
  i = 0;
  if (word1 == NULL)
    return (0);
  while (word1[n] != '\0' && word2[n] != '\0' && word1[n] == word2[n])
    {
      n += 1;
      i += 1;
    }
  while (word1[i] == ' ' || word1[i] == '\t')
    i += 1;
  if (n == my_strlen(word2) && word1[i] == '\0')
    return (1);
  return (0);
}

int	ini_env(t_env *ev)
{
  ev->val_exit = 0;
  ev->state_p = 0;
  ev->result = 0;
  ev->oldpwd = NULL;
  if ((ev->stdin = dup(0)) == -1
      || (ev->stdout = dup(1)) == -1)
    return (-1);
  return (0);
}

int		main(int ac UNUSED, char **av UNUSED, char **environ)
{
  t_env		ev;
  t_history	history;
  char		*buffer;
  t_info	info;

  buffer = NULL;
  if (ini_env(&ev) == -1
      || (ev.env = create_my_env(environ, 0, 0, &ev)) == NULL)
    return (0);
  /* init_fct(&history, &ev, environ, &info); */
  while (1)
    {
      if (isatty(0) == 1)
	my_putstr("prompt$>");
      if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	return (ev.val_exit);
      if (buffer != NULL)
	free(buffer);
      if ((buffer = get_next_line()) == NULL)
	return (ev.val_exit);
      if (buffer[0] != '\0')
	{
	  if (valid_line(buffer) == 0
	      && (ev.env = next_step(buffer, &ev)) == NULL)
	    return (ev.val_exit);
	}
    }
  return (ev.val_exit);
}

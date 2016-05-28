/*
** main.c for main in /home/wery_p/rendu/PSU_2015_minishell1
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jan 16 20:40:01 2016 Paul Wery
** Last update Sat May 28 23:34:14 2016 Paul Wery
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
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
  char		**pars;
  t_exec	*list;
  int		n;

  if ((n = equal_w_space("echo", buffer)) != 0)
    echo_built(buffer, n);
  else
    {
      if ((pars = pars_elems(buffer)) == NULL
	  || (list = create_list()) == NULL
	  || full_list(list, pars) == -1
	  || (ev->env = exec_list(list, ev)) == NULL
	  || default_io(ev->stdin, ev->stdout, 3) == -1)
	return (NULL);
      free_opts(pars);
      delete_list(&list);
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
  ev->state_p = 0;
  ev->result = 0;
  ev->oldpwd = NULL;
  if ((ev->stdin = dup(0)) == -1
      || (ev->stdout = dup(1)) == -1)
    return (-1);
  return (0);
}

int	main(int ac UNUSED, char **av UNUSED, char **environ)
{
  t_env	ev;
  char	*buffer;

  buffer = NULL;
  if (ini_env(&ev) == -1 || (ev.env = create_my_env(environ, 0, 0)) == NULL)
    return (0);
  while (1)
    {
      my_putstr("prompt$>");
      if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	return (0);
      if (buffer != NULL)
	free(buffer);
      if ((buffer = get_next_line()) == NULL)
	return (0);
      if (buffer[0] != '\0')
	{
	  my_exit(buffer, "exit", buffer, &ev);
	  if (valid_line(buffer) == 0
	      && (ev.env = next_step(buffer, &ev)) == NULL)
	    return (0);
	}
    }
  return (0);
}

/*
** init_history.c for 42sh in /home/gerard_v/Documents/42sh/srcs
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#include "get_line.h"

char	*get_history_file(char *home)
{
  char	*path;

  if (home == NULL)
    return (NULL);
  path = malloc(strlen(home) + strlen("/.42sh_history") + 1);
  if (path == NULL)
    return (NULL);
  strcpy(path, home);
  strcat(path, "/.42sh_history");
  return (path);
}

int	init_commands(t_history *history, char **envp)
{
  history->commands.first = NULL;
  history->commands.last = NULL;
  history->commands.size = 0;
  history->history_file = get_history_file(my_gethome(envp));
  if (history->history_file == NULL)
    return (1);
  history->current_cmd = NULL;
}

int  	init_history(t_history *history, char **envp)
{
  if (init_commands(history,envp) == 1)
    return (1);
  if (read_file(history) == 1)
    return (1);
  history->current_cmd = history->commands.last;
  return (0);
}

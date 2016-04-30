/*
** parser.c for parser.c in /home/cheval_8/rendu/PSU_2015_minishell2
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
**
** Started on  Mon Mar 28 22:12:16 2016 Chevalier Nicolas
** Last update Tue Apr 12 23:37:37 2016 Chevalier Nicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

void		add_pipe(int **pipe_fd, t_command *command, int fd[2], int j)
{
  if ((pipe(fd)) == -1)
    exit (0);
  command->output = fd[1];
  (*pipe_fd)[j] = fd[0];
  (*pipe_fd)[j + 1] = fd[1];
  (*pipe_fd)[j + 2] = 0;
}

void		pipe_in_list(char **tmp, t_list *list, int **pipe_fd, int nb_pipe)
{
  t_command	*command;
  int		fd[2];
  int		i;
  int		j;

  i = 0;
  j = 0;
  if ((command = malloc(sizeof(t_command))) == NULL)
    exit (0);
  init_struct(command);
  while (nb_pipe > 0)
    {
      add_pipe(pipe_fd, command, fd, j);
      command->data = my_str_to_wordtab(tmp[i++], ' ');
      my_insert_pushfront(list, command);
      command->input = fd[0];
      j += 2;
      nb_pipe -= 1;
    }
  command->output = -1;
  command->data = my_str_to_wordtab(tmp[i], ' ');
  my_insert_pushfront(list, command);
}

char		*list_command(t_list *list, char **tmp, int **pipe_fd)
{
  char		*error;
  t_command	*command;
  int		nb_pipe;
  int		i;

  (*pipe_fd) = NULL;
  nb_pipe = -1;
  i = -1;
  while (tmp[++i] != '\0')
    nb_pipe += 1;
  if (nb_pipe > 0)
    if ((*(pipe_fd) = malloc(sizeof(int) * (nb_pipe * 2 + 1))) == NULL)
      exit (0);
  pipe_in_list(tmp, list, pipe_fd, nb_pipe);
  command = list->first;
  if ((error = redirection_in_list(&command)) != 0)
    return (error);
  return (0);
}

char		*parser(char *tab, t_env *env)
{
  char		**command;
  int		*pipe_fd;
  t_command	*tmp;
  t_list	list;
  int		nb_exec;
  char		*error;

  nb_exec = 0;
  init_list(&list);
  command = separe_wordtab(tab, '|');
  if ((error = list_command(&list, command, &pipe_fd)) != 0)
    return (error);
  tmp = list.first;
  while (tmp != NULL)
    {
      if (my_execve(tmp, tmp->redirection,
		    env, pipe_fd) != 42)
	nb_exec += 1;
      tmp = tmp->next;
    }
  close_fd(pipe_fd);
  loop_wait(nb_exec);
  return (0);
}

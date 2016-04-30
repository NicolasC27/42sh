/*
** my_exec.c for my_exec.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Jan 14 03:43:02 2016 Nicolas Chevalier
** Last update Tue Apr 12 23:01:39 2016 Chevalier Nicolas
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

char		**check_alias(char **command)
{
  if (my_strcmp(command[0], "lc", 0))
    return (my_str_to_wordtab("ls --color", ' '));
  if (my_strcmp(command[0], "ll", 0))
    return (my_str_to_wordtab("ls -alF --color", ' '));
  if (my_strcmp(command[0], "ne", 0))
    return (my_str_to_wordtab("emacs -nw", ' '));
  if (my_strcmp(command[0], "la", 0))
    return (my_str_to_wordtab("ls -lA --color", ' '));
  if (my_strcmp(command[0], "clean", 0))
    return (my_str_to_wordtab("rm -f *~ ; -f *#", ' '));
  return (command);
}

char		test_file(char opt, char opt2, char **command)
{
  if (opt != ' ')
    {
      if (command[0][0] == opt && command[0][1] == opt2
	  && (access(command[0], F_OK) != -1))
	return (0);
    }
  else if (opt == ' ')
    if (command[0][0] == opt2 && (access(command[0], F_OK) != -1))
      return (0);
  return (1);
}

char		*recursive_execve(char **path, char **command, char **tabenv, int i)
{
  char		*filename;

  filename = NULL;
  if (!test_file('.', '/', command))
    {
      if (((filename = command[0]) && (access(command[0], R_OK | X_OK) == -1))
	  || (execve(filename, command, tabenv) == -1))
	return ("Permissions denied.");
    }
  else if (command[0][0] != '/' && command[0][0] != '.')
    filename = my_strcat(path[i++], command[0], 1);
  else if (!test_file(' ', '/', command))
    if (((filename = command[0]) && (access(command[0], R_OK | X_OK) == -1))
	|| (execve(filename, command, tabenv) == -1))
      return ("Permissions denied.");
  if (filename != NULL)
    {
      execve(filename, command, tabenv);
      recursive_execve(path, command, tabenv, i);
    }
  else
    return (NULL);
  return (0);
}

static void	execve_error(char *error, char **command, char **tabenv)
{
  my_puterror_execve(error, command);
  my_free(command);
  my_free(tabenv);
  exit(EXIT_FAILURE);
}

int		my_execve(t_command *command, t_redirection **redirection,
			  t_env *env, int *pipe_fd)
{
  char		**tabenv;
  char		*error;
  pid_t		pid;

  if (check_command(command, env) != 42)
    return (42);
  else if ((pid = fork()) == 0)
    {
      my_execve_canals(command, redirection);
      close_fd(pipe_fd);
      tabenv = conv_list(env);
      error = recursive_execve(
			       my_str_to_wordtab(pathornotpath(search_env(env, "PATH")), ':'),
			       check_alias(command->data), tabenv, 0);
      execve_error(error, command->data, tabenv);
    }
  else if (pid == -1)
    my_putstr("Impossible, error with pid");
  return (0);
}

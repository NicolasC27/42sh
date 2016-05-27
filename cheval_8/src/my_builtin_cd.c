/*
** my_builin.c for my_builtin.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Thu Jan 14 15:20:14 2016 Nicolas Chevalier
** Last update Tue Apr 12 22:06:31 2016 Chevalier Nicolas
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "my.h"

static char	*get_pwd()
{
  char		*pwd;

  if ((pwd = malloc(sizeof(char *) * 1024)) == NULL)
    my_puterror("Error with a memory allocation(5)");
  getcwd(pwd, 1024);
  return (pwd);
}

char		*update_env_cd(t_env *env, char *change)
{
  char		*buff;

  if (search_env(env, change) != NULL)
    {
      if ((buff = malloc(sizeof(char *) * 1024)) == NULL)
      	my_puterror("Error with a memory allocation(5)");
      getcwd(buff, 1024);
      env = update_env(env, my_strcat(my_strcat(change, "=", 0),
				      buff, 0), change);
      free(buff);
    }
  return (NULL);
}

char		*check_directory(t_env *env, char *command, char *oldpwd)
{
  char		*dir;

  if (command == NULL || my_strcmp(command, " ", 0)
      || my_strcmp(command, "\t", 0) || my_strcmp(command, "\0", 0))
    dir = search_env(env, "HOME");
  else if (my_strcmp(command, "-", 0))
    dir = (oldpwd == NULL) ? "\0" : oldpwd;
  else if (my_strcmp(command, "~", 0))
    dir = search_env(env, "HOME");
  else
    dir = command;
  return (dir);
}

char		my_builtin_cd(char **command, t_env *env)
{
  static char	*oldpwd;
  char		*dir;

  if ((dir = check_directory(env, command[1], oldpwd)) == NULL)
    return (0);
  if (access(dir, F_OK) == -1)
    return (my_puterrorcd("No such file or directory.", dir));
  if (access(dir, R_OK) == -1)
    return (my_puterrorcd("Permission denied.", dir));
  oldpwd = get_pwd();
  if (chdir(dir) == -1)
    return (my_puterrorcd("You cannot change the dir.", dir));
  update_env_cd(env, "PWD");
  return (0);
}

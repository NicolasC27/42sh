/*
** main.c for main.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Jan  5 15:30:29 2016 Nicolas Chevalier
** Last update Thu May 12 16:25:52 2016 Nicolas Chevalier
*/

#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "gnl.h"
#include "my.h"

/*
** Print custom prompt
*/
void		my_prompt(t_env *env, int nb)
{
  char		*user;
  char		*pwd;

  user = search_env(env, "USER");
  pwd = search_env(env, "PWD");
  if (nb == 1)
    my_putstr(START_SHELL);
  if (user != NULL || pwd != NULL)
    {
      my_putstr(RED"(");
      if (user)
	my_putstr(user);
      if (pwd)
	{
	  my_putstr("@"CYAN);
	  my_putstr(pwd);
	}
      my_putstr(RED")");
    }
  my_putstr(RED"->"DEFAULT);
}

char		minishell(char *buff, t_env *env)
{
  char		**tab;
  char		*error;
  int		i;

  i = -1;
  (void)(*env);
  tab = separe_wordtab(buff, ';');
  while (tab[++i])
    {
      error = parser(tab[i], env);
      if (error != 0)
      	my_putstr(error);
    }
  my_free(tab);
  return (0);
}

void		my_control_c(int c)
{
  (void)c;
  my_putstr("\033[1;31m");
  my_putstr("\n->");
  my_putstr("\033[1;0m");
}

void		my_signal()
{
  if (signal(SIGINT, my_control_c) == SIG_ERR)
    my_puterror("error: problem wit signal SIGInt.\n");
}

int			mode(int i, int option)
{
  static struct termios	oldT;
  static struct termios	newT;

  if (i == 0)
    {
      ioctl(0, TCGETS, &oldT);
      ioctl(0, TCGETS, &newT);

      newT.c_lflag &= ~(ICANON);
      newT.c_lflag &= ~(ECHO);
      if (option == 1)
	{
	  newT.c_cc[VMIN] = 1;
	  newT.c_cc[VTIME] = 0;
	}
      ioctl(0, TCSETS, &newT);
    }
  if (i == 1)
    ioctl(0, TCSETS, &oldT);
  return (0);
}

char		*my_autocomplete(char *str)
{
  char		*buff;
  int		len;
  /* struct dirent	*dirent; */
  /* DIR		*dir; */

  /* if ((dir = opendir("./")) == NULL) */
  /*   { */
  /*     my_putstr("ERROR"); */
  /*     exit(0); */
  /*   } */
  /* my_putstr("\n"); */
  /* while ((dirent = readdir(dir))) */
  /*   { */
      /* if (dirent->d_name[0] != '.') */
      /* 	my_putstr(dirent->d_name); */
      /* my_putstr(" "); */
    /* } */
  return (str);
}

char		*get_line()
{
  char		*str;
  char		buff[9];
  int		len;
  int		i;

  mode(0, 1);
  /* buff = get_next_line(0); */
  len = 1;
  i = 0;
  str = NULL;
  while (len > 0)
    {
      if ((len = read(0, buff, 9)) == -1)
	return (NULL);
      buff[len] = '\0';
      my_putstr(buff);
      if (buff[0] == '\n' && buff[1] == '\0')
	return (str);
      if (buff[0] == '\t')
      	return (my_autocomplete(str));
      str = realloc(str, i + 2);
      str[i] = buff[0];
      str[i + 1] = '\0';
      i += 1;

    }
  mode(1, 0);
  str = my_strdup(buff);
  /* exit (0); */
  return (str);
}

int		main(int argc, char **argv, char **envp)
{
  t_env		*env;
  char		*buff;

  UNUSED(argc);
  UNUSED(**argv);
  buff = NULL;
  if (envp[0] == NULL)
    envp[0] = NULL;
  env = init_listenv(envp);
  my_prompt(env, 1);
  while ((buff = get_line()))
    {
      if (buff != NULL)
	minishell(buff, env);
      my_prompt(env, 2);
      my_signal();
      free(buff);
    }
  my_putstr(STOP_SHELL);
  return (0);
}

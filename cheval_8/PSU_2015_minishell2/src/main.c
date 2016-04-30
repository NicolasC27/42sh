/*
** main.c for main.c in /home/cheval_8/rendu/PSU_2015_minishell1
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Jan  5 15:30:29 2016 Nicolas Chevalier
** Last update Sat Apr 30 19:01:41 2016 Nicolas Chevalier
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
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

int		main(int argc, char **argv, char **envp)
{
  t_env		*env;
  char		*buff;

  UNUSED(argc);
  UNUSED(**argv);
  if (envp[0] == NULL)
    envp[0] = NULL;
  env = init_listenv(envp);
  my_prompt(env, 1);
  init_term()
  while ((buff = get_next_line(0)))
    {
      minishell(buff, env);
      my_prompt(env, 2);
      my_signal();
      free(buff);
    }
  my_putstr(STOP_SHELL);
  return (0);
}

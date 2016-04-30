/*
** my.h for my.h in /home/cheval_8/rendu/PSU_2015_minishell1/includes
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue Jan  5 16:32:16 2016 Nicolas Chevalier
// Last update Thu Apr 14 02:44:09 2016 Chevalier Nicolas
*/

#ifndef MY_H_
# define MY_H_

/*
** Includes
*/
#include "lib.h"

/*
** Defines
*/
#define UNUSED(x)	(void)(x)
#define START_SHELL	RED "Minishell 2 working ...\n" DEFAULT
#define STOP_SHELL	RED "Minishell 2 stopeed ...\n" DEFAULT

typedef struct		s_redirection
{
  char			**tab;
  int			redi_left;
  int			redi_right;
  int			redi_two_right;
  int			redi_two_left;
}			t_redirection;

typedef struct		s_command
{
  char			**data;
  int			fd;
  int			output;
  int			nb_redirection;
  t_redirection		**redirection;
  int			input;
  struct s_command	*next;
  struct s_command	*prev;
}			t_command;

typedef struct		s_list
{
  t_command		*first;
  t_command		*last;
}			t_list;

typedef struct		s_env
{
  char			*data;
  struct s_env		*next;
  struct s_env		*prev;
}			t_env;

/*
** wait.c
*/
void		loop_wait(int);
/*
** init.c
*/
void		init_struct(t_command *);
void		init_struct_redirection(t_command **, int);

/*
** my_exec_canals
*/
int		my_execve_canals(t_command *, t_redirection **);
void		close_fd(int *);

/*
** redirection.c
*/
char		*redirection_in_list(t_command **);

/*
** separe_wordtab.c
*/
char		**separe_wordtab(char *, char);
char		**separe_redirection(char **);

/*
** init_envenv.c
*/
t_env		*create_node();
t_env		*init_listenv(char **);
t_env		*add_env(t_env *, char *, char *);

/*
** parser.c
*/
char		*parser(char *, t_env *);

/*
** my_puterror.c
*/
void		my_puterror(char *);
char		my_puterrorcd(char *, char *);
char		my_puterror_execve(char *, char **);

/*
** my_builtin.c
*/
char		my_builtin_exit(char **, t_env *);
char		*check_directory(t_env *, char *, char *);
char		my_builtin_cd(char **, t_env *);
char		my_builtin_env(char **, t_env *);
char		my_builtin_unsetenv(char **, t_env *);
char		my_builtin_setenv(char **, t_env *);

/*
** utils.c
*/
int		count_env(t_env *, t_env *);
void		my_free(char **);
void		my_putchar_err(char);
void		my_putstr_err(char *);
int		count_list(t_env *, t_env *);

/*
** utils_env.c
*/
void		display_env(t_env *);
char		**conv_list(t_env *);
char		*search_env(t_env *, char *);
t_env		*update_env(t_env *, char *, char *);
void		remove_env(t_env *, char *);

/*
** check_command.c
*/
char		*pathornotpath(char *);
char		*verif_path(char *);
char		*my_find_element(char *, t_env *);
char		check_command(t_command *, t_env *);
int		my_builtin(t_command *, t_env *);

/*
** my_exec.c
*/
int		my_execve(t_command *, t_redirection **, t_env *, int *);
char		*recursive_execve(char **, char **, char **, int);

/*
** list.c
*/
void		init_list(t_list *);
int		my_insert_pushfront(t_list *, t_command *);
int		my_insert_pushback(t_list *, t_command *);

/*
** my_str.c
*/
int		my_strlen(char *);
char		*my_strdup(char *);
char		*my_strcat(char *, char *, int);
int		my_strlen(char *);
char		*my_strdup(char *);
char		my_strcmp(char *, char *, int);

/*
** my_getnbr.c
*/
int		my_getnbr(char *);

#endif /* !MY_H_ */

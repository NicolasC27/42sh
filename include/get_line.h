/*
** get_line.h for get_line.h in /home/cheval_8/rendu/PSU_2015_42sh/srcs/get_line
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:48:14 2016 Nicolas Chevalier
** Last update Sun Jun  5 08:55:17 2016 Nicolas Chevalier
*/

#ifndef GET_LINE_H_
# define GET_LINE_H_

/*
** Defines
*/

# define UP		65
# define DOWN		66
# define LEFT		68
# define RIGHT		67
# define DELETE		51
# define POS_CUR	"\033[6n"
# define CLEAR		12
# define BLACK		"\033[0;30m"
# define RED		"\033[1;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[1;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define GREY		"\033[0;37m"
# define DEFAULT	"\033[0;m"

/*
** Includes
*/
# include <stdbool.h>
# include "history.h"

typedef struct	s_info
{
  char		*keyleft;
  char		*keyup;
  char		*keyright;
  char		*keydown;
  char		*pos_begin;
  bool		term;
  int		fd;
}		t_info;

typedef struct	s_edit
{
  char		*cmd;
  int		len;
  int		pos;
}		t_edit;


/*
**prompt.c
*/
int		prompt(char **);

/*
**init_fct.c
*/
void		init_fct(t_history *,  char **, t_info *);

/*
** get_line.c
*/
char		*get_line(t_history *history, t_info *, char **);

/*
** getterm.c
*/
char		*my_getterm(char **);

/*
** my_strncmp.c
*/
char		my_strncmp(char *, char *, int);

/*
** mode.c
*/
int		mode(int, int, int);

/*
** keyboard.c
*/
int		keyboard(t_edit *, char *, t_history *, t_info *);

/*
** init.c
*/
char		*init(t_edit *, char **);

/*
** history.c
*/
int		history_func(t_edit *, t_history *, char *, t_info *);

/*
** autocomplete.c
*/
char		*my_autocomplete(char *str);

/*
** cursor.c
*/
int		cursors_left(t_edit *, t_info *);
int		cursors_right(t_edit *, t_info *);
int		cursors_delete(t_edit *, char *, t_info *);

/*
** character.c
*/
void		add_character_advanced(t_edit *, char, t_info *);
void		add_character_normal(t_edit *, char);

#endif /* !GET_LINE_H_ */

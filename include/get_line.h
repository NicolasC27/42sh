/*
** get_line.h for get_line.h in /home/cheval_8/rendu/PSU_2015_42sh/srcs/get_line
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:48:14 2016 Nicolas Chevalier
** Last update Sun Jun  5 03:11:08 2016 Nicolas Chevalier
*/

#ifndef GET_LINE_H_
# define GET_LINE_H_

#define	UP	65
#define	DOWN	66
#define	LEFT	68
#define	RIGHT	67
#define DELETE	51
#define POS_CUR	"\033[6n"
#define CLEAR	12
# include "history.h"

typedef struct	s_info
{
  char		*keyleft;
  char		*keyup;
  char		*keyright;
  char		*keydown;
  char		*pos_begin;
}		t_info;

typedef struct	s_edit
{
  char		*cmd;
  int		len;
  int		pos;
}		t_edit;

/*
**init_fct.c
*/
void	init_fct(t_history *,  char **, t_info *);

/*
** get_line.c
*/
char		*get_line(t_history *history);

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
int		keyboard(t_edit *, char *, t_history *);

/*
** init.c
*/
char		*init(t_edit *);

/*
** history.c
*/
int		history_func(t_edit *, t_history *, char *);

/*
** autocomplete.c
*/
char		*my_autocomplete(char *str);

/*
** cursor.c
*/
int		cursors_left(t_edit *);
int		cursors_right(t_edit *);
int		cursors_delete(t_edit *, char *);

/*
** character.c
*/
void		add_character_advanced(t_edit *, char);
void		add_character_normal(t_edit *, char);

#endif /* !GET_LINE_H_ */

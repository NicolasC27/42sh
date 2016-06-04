/*
** get_line.h for get_line.h in /home/cheval_8/rendu/PSU_2015_42sh/srcs/get_line
**
** Made by Nicolas Chevalier
** Login   <cheval_8@epitech.net>
**
** Started on  Tue May 31 10:48:14 2016 Nicolas Chevalier
** Last update Sat Jun  4 15:10:27 2016 Nicolas Chevalier
*/

#ifndef GET_LINE_H_
# define GET_LINE_H_

#define	UP	65
#define	DOWN	66
#define	LEFT	67
#define	RIGHT	68
#define POS_CUR	"\033[6n"

typedef struct	s_info
{
  char		*keyleft;
  char		*keyup;
  char		*keyright;
  char		*keydown;
}		t_info;

typedef struct	s_edit
{
  char		*cmd;
  int		len;
  int		pos;
}		t_edit;

/*
** get_line.c
*/
char		*get_line(char **);

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
int		keyboard(t_edit *, char *);

/*
** init.c
*/
char		*init(t_edit *, t_info *, char **);

#endif /* !GET_LINE_H_ */

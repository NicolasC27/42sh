/*
** history.h for 42sh in /home/gerard_v/Documents/42sh/includes
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Sun Jun  5 07:58:13 2016 Nicolas Chevalier
*/

#ifndef HISTORY_H_
# define HISTORY_H_

# define HISTORY_FILE "/home/cheval_8/.42sh_history"

# include <sys/ioctl.h>
# include <string.h>
# include <fcntl.h>
# include <termios.h>
# include "get_next_line.h"

/*
** Cmd_struct
*/
typedef struct	s_cmd
{
  char		*command;
  int		length;
  struct s_cmd	*next;
  struct s_cmd	*prev;
}		t_cmd;

typedef struct	s_commands
{
  t_cmd		*first;
  t_cmd		*last;
  int		size;
}		t_commands;

/*
** History_struct
*/
typedef struct		s_history
{
  t_commands		commands;
  t_cmd			*current_cmd;
  int			press;
  struct termios	oldt;
  struct termios	newt;
}			t_history;

/*
** Functions
*/
void	canonical_mode(struct termios *oldt, struct termios *newt, int mode);
int	add_command(t_commands *commands, t_cmd *cmd);
int	init_history(t_history *history);
void   	free_commands(t_commands *commands);
void	my_putchar_out(char c, int out);
void	my_putstr_out(char *str, int out);
int	my_strlen_out(char *str);

/*
** File
*/
int	open_file(char *file_name, int mode);
int    	open_error(char *file_name);
int	read_file(t_commands *commands);
int	write_file(t_commands *commands);
int    	close_file(int id);
int    	close_error(char *file_name);

#endif /* !HISTORY_H_ */

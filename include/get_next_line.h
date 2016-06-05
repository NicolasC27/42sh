/*
** get_next_line.h for 42sh in /home/gerard_v/Documents/42sh/includes
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Wed Dec 30 00:49:51 2015 Valentin GERARD
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# ifndef READ_SIZE
#  define READ_SIZE (14)
# endif /* !READ_SIZE */

#include <stdlib.h>
#include <unistd.h>

typedef struct	s_prog
{
  int		i;
  int		k;
  int		fd;
  char		*return_line;
}		t_prog;

char	*get_next_linee(int fd);

#endif /* !GET_NEXT_LINE_H_ */

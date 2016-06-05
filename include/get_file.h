/*
** get_next_line.h for header getnextline in /home/carbon_b/getnexline
** 
** Made by Guillaume CARBONNIER
** Login   <carbon_b@epitech.net>
** 
** Started on  Mon Jan  4 11:11:19 2016 Guillaume CARBONNIER
** Last update Sat Jun  4 22:58:14 2016 carbon_b
*/

# ifndef READ_SIZ
#  define READ_SIZ (512)
# endif  /* !READ_SIZ */

# ifndef GET_FILE_H_
#  define GET_FILE_H_

#include <unistd.h>
#include <stdlib.h>

typedef struct s_tmp
{
  char *line;
  int	i;
  char	c;
}t_tmp;

char	*get_file(const int fd);

# endif /* !GET_FILE_H_ */

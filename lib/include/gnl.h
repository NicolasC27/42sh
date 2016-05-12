/*
** gnl.h for gnl.h in /home/cheval_8/test/CPE_2015_Allum1/include
**
** Made by Chevalier Nicolas
** Login   <cheval_8@epitech.net>
** Started on  Sun Feb 21 01:05:11 2016 Chevalier Nicolas
// Last update Sat Apr  2 18:12:51 2016 Chevalier Nicolas
*/

#ifndef GNL_H_
# define GNL_H_

/*
** Includes
*/
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

/*
** Define
*/
# define BUFF_SIZE	4096

/*
** Get_next_line.c
*/
char		*get_next_line(const int);

/*
** my_strlen.c
*/
int		my_strlen(char *);

/*
** my_realloc.c
*/
char		*my_realloc(char *, int);

/*
** my_memset.c
*/
void		*my_memset(void *, int, int);

#endif /* !GNL_H_ */

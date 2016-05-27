##
## Makefile for Makefile in /home/cheval_8/PSU_2015_minitalk/lib
## 
## Made by Chevalier Nicolas
## Login   <cheval_8@epitech.net>
## 
## Started on  Thu Feb 18 19:58:40 2016 Chevalier Nicolas
## Last update Sun Apr 10 03:45:40 2016 Chevalier Nicolas
##

NAME	= libmyutils.a

SRCS	= my_putchar.c \
	  my_getnbr.c \
	  my_put_nbr.c \
	  my_putstr.c \
	  my_strlen.c \
	  my_write.c \
	  my_realloc.c \
	  my_memset.c \
	  gnl/get_next_line.c \
	  concat.c \
	  my_strncmp.c \
	  my_str_to_wordtab.c \
	  my_putstr_err.c

MOD	= $(addprefix src/, $(SRCS:.c=.o))

CFLAGS	+= -W -Wall -Wextra
CFLAGS	+= -ansi -pedantic
CFLAGS	+= -Iinclude/

RM	= rm -rf

all:	$(NAME)

$(NAME):  $(MOD)
	  ar rc $(NAME) $(MOD)

clean:	
	$(RM) $(MOD)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

##
## Makefile for tetris in /home/cheval_8/rendu/PSU_2015_tetris
##
## Made by Chevalier Nicolas
## Login   <cheval_8@epitech.net>
##
## Started on  Wed Feb 24 16:02:04 2016 Chevalier Nicolas
## Last update Thu May 19 09:50:07 2016 Nicolas Chevalier
##


NAME		=	42sh

SRC		= 	main.c \
			utils.c \
			parser.c \
			env/init_listenv.c \
			separe.c \
			check_command.c \
			env/utils_env.c \
			my_exec.c \
			my_str.c \
			my_builtin.c \
			my_builtin_cd.c \
			my_getnbr.c \
			my_free.c \
			init.c \
			my_puterror.c \
			redirection.c \
			my_exec_canals.c \
			wait.c \
			list/list.c 

MOD		=	$(addprefix src/, $(SRC:.c=.o))

LIB		=	-Llib/
LIB		+=	-Ilib/include -Llib/ -lmyutils

LIBMYUTILS_MAKE	=	make -C lib/
LIBMYUTILS	=	lib/libmyutils.a

# CFLAGS		=	-W -Wall -Werror -Wextra
CFLAGS		+=	-Wno-overlength-strings
CFLAGS		+=	-g
CFLAGS		+=	-Iinclude/
CFLAGS		+=	-D_BSD_SOURCE -D_POSIX_SOURCE
CFLAGS		+=	$(LIB)

LDFLAGS		=	$(LIB)

all:		$(LIBMYUTILS) $(NAME)

$(NAME):	$(MOD)
		@cc $(MOD) -o $(NAME) $(LDFLAGS) -lncurses

$(LIBMYUTILS):
	 	$(LIBMYUTILS_MAKE)

clean		:
		 rm -rf $(MOD)
		 $(LIBMYUTILS_MAKE) clean

fclean		: clean
		  rm -rf $(NAME)
		  $(LIBMYUTILS_MAKE) fclean

re:		fclean all

.PHONY:		all clean fclean re

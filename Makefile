##
## Makefile for makefile in /home/wery_p/rendu/PSU_2015_minishell2
##
## Made by Paul Wery
## Login   <wery_p@epitech.net>
##
## Started on  Sat Apr  2 00:37:51 2016 Paul Wery
## Last update Sat Jun  4 21:25:53 2016 Paul Wery
##

NAME    =	42sh

RM      =	rm -f

CC	=	gcc -g

CFLAGS	=	-W -Wall -Werror -Iinclude

OBJS    =	$(SRCS:.c=.o)

SRCS    =	srcs/main.c \
		srcs/my_list.c \
		srcs/pars_elems.c \
		srcs/full_list.c \
		srcs/strings_files.c \
		srcs/command_exec.c \
		srcs/change_std.c \
		srcs/change_std_next.c \
		srcs/gest_files.c \
		srcs/red_left.c \
		srcs/and_or.c \
		srcs/echo.c \
		srcs/pair.c \
		srcs/echo_next.c \
		srcs/notm.c \
		srcs/exec/get_next_line.c \
		srcs/exec/exec_line.c \
		srcs/exec/make_path.c \
		srcs/exec/my_put_error.c \
		srcs/exec/only_exec.c \
		srcs/exec/my_exit.c \
		srcs/exec/valid_line.c \
		srcs/exec/alloc_buffer.c \
		srcs/builtins/my_builtins.c \
		srcs/builtins/create_my_env.c \
		srcs/builtins/unset_env.c \
		srcs/builtins/set_env.c \
		srcs/builtins/set_env2.c \
		srcs/builtins/cd_return.c \
		srcs/builtins/swap_env.c \
		srcs/builtins/fonc_cd.c \
		srcs/builtins/if_empty_path.c \
		srcs/builtins/final_env.c \
		srcs/builtins/conv_fonc.c \
		srcs/inhib/inhib_fonc.c \
		srcs/global/order_list.c \
		srcs/global/order_names.c \
		srcs/global/glob_one/echo_star.c \
		srcs/global/glob_one/replace_seg.c \
		srcs/global/glob_two/echo_quest.c \
		srcs/global/glob_two/replace_seg_q.c \
		srcs/global/glob_three/echo_bracket.c \
		srcs/global/glob_three/replace_seg_b.c \
		srcs/global/glob_three/match_brak.c \
		srcs/var_env/replace_var.c \
		srcs/var_env/replace_seg_v.c \
		srcs/var_env/get_val_ret.c \
		srcs/parsing_error.c \

$(NAME) :	$(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all     :	$(NAME)

clean   :
	$(RM) $(OBJS)

fclean  :	clean
	$(RM) $(NAME)

re      :	fclean all

.PHONY: all clean fclean re

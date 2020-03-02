# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/21 14:20:54 by gel-kasr          #+#    #+#              #
#    Updated: 2020/03/02 11:37:21 by gel-kasr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		minishell
SRCS =		srcs/minishell.c \
			srcs/display_prompt.c \
			srcs/exec_cmd.c \
			srcs/signals.c \
			srcs/builtin_env.c \
			srcs/str_utils.c \
			srcs/find_exec_path.c \
			srcs/parser.c \
			srcs/env_var.c \
			srcs/quotes.c \
			srcs/builtins/exec_builtins.c \
			srcs/builtins/split_in_2.c \
			srcs/builtins/echo/ft_echo.c \
			srcs/builtins/cd/ft_cd.c \
			srcs/builtins/pwd/ft_pwd.c \
			srcs/builtins/exit/ft_exit.c \
			srcs/builtins/export/ft_export.c \
			srcs/builtins/export/export_no_param.c \
			srcs/builtins/env/ft_env.c \
			srcs/builtins/unset/ft_unset.c \
			srcs/termios/term.c \
			srcs/termios/term_utils.c \
			srcs/termios/cursor.c \
			srcs/termios/reader.c \
			srcs/termios/add_delete_in_buffer.c \
			srcs/termios/histo.c \


OBJS =		$(SRCS:%.c=%.o)
DEP = 		$(OBJS:%.o=%.d)

INC_DIR = 	includes/
HEADER = 	$(INC_DIR)minishell.h \
			$(INC_DIR)term_bonus.h \

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
MAKE = 		make
HFLAGS =	-I $(INC_DIR) -I $(LIBFT_INC)
DEBUG =		-Wall -Wextra -Werror -g3 -fsanitize=address
LINUX =		-Wall -Wextra

CURRENT_FLAGS = $(CFLAGS)

LIBFT_DIR =	libft/
LIBFT_INC = $(LIBFT_DIR)includes/
LIBFT =		$(LIBFT_DIR)libft.a
LIBFT_H = 	$(LIBFT_INC)libft.h

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CURRENT_FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lncurses

.c.o:
			$(CC) -c $(CURRENT_FLAGS) -MMD -MP $(HFLAGS) $< -o $(<:.c=.o)

$(LIBFT):
			make -C $(LIBFT_DIR)

clean:
			rm -f $(OBJS) $(DEP)

cleanall:	clean
			make clean -C $(LIBFT_DIR)

fclean:		clean
			rm -f $(NAME)

fcleanall:	cleanall
			make fclean -C $(LIBFT_DIR)

re:			fclean all

reall:		fcleanall re

norm:
			norminette $(SRCS) $(HEADER)
normall:
			norminette $(SRCS) $(HEADER)
			make norm -C $(LIBFT_DIR)

test:		$(NAME)
			./debug/tests/tester.sh

main:		$(NAME)
			./$(NAME)

.PHONY:		all re norm normall clean fclean main save fcleanall reall test

-include 	$(DEP)

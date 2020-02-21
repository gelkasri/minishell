#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/21 13:57:16 by gel-kasr          #+#    #+#              #
#    Updated: 2020/02/21 13:58:13 by gel-kasr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 		minishell
SRCS =		srcs/minishell.c \

OBJS =		$(SRCS:%.c=%.o)
DEP = 		$(OBJS:%.o=%.d)

INC_DIR = 	includes/
HEADER = 	$(INC_DIR)minishell.h \

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
MAKE = 		make
HFLAGS =	-I $(INC_DIR) -I $(LIBFT_INC)

LIBFT_DIR =	libft/
LIBFT_INC = $(LIBFT_DIR)includes/
LIBFT =		$(LIBFT_DIR)libft.a
LIBFT_H = 	$(LIBFT_INC)libft.h

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(OBJS) $(LIBFT) -o $(NAME)

.c.o:
			$(CC) -c $(CFLAGS) -MMD -MP $(HFLAGS) $< -o $(<:.c=.o)

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

main:		$(NAME)
			./$(NAME)

.PHONY:		all re norm normall clean fclean main save fcleanall reall

-include 	$(DEP)

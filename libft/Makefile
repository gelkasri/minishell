# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 14:29:53 by gel-kasr          #+#    #+#              #
#    Updated: 2020/02/24 15:33:33 by mle-moni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libft.a
SRCS =		srcs/ft_putchar_fd.c \
			srcs/ft_putstr_fd.c \
			srcs/ft_putendl_fd.c \
			srcs/ft_putnbr_fd.c \
			srcs/ft_putchar.c \
			srcs/ft_putstr.c \
			srcs/ft_print_hexa.c \
			srcs/ft_putstr_non_printable.c \
			srcs/ft_putendl.c \
			srcs/ft_putnbr.c \
			srcs/ft_putnchar_fd.c \
			srcs/ft_putnchar.c \
			srcs/ft_strlen.c \
			srcs/ft_isupper.c \
			srcs/ft_islower.c \
			srcs/ft_isalpha.c \
			srcs/ft_isdigit.c \
			srcs/ft_isalnum.c \
			srcs/ft_isascii.c \
			srcs/ft_isprint.c \
			srcs/ft_isspace.c \
			srcs/ft_toupper.c \
			srcs/ft_tolower.c \
			srcs/ft_bzero.c \
			srcs/ft_memalloc.c \
			srcs/ft_memdel.c \
			srcs/ft_memset.c \
			srcs/ft_memcpy.c \
			srcs/ft_memccpy.c \
			srcs/ft_memmove.c \
			srcs/ft_strcmp.c \
			srcs/ft_strncmp.c \
			srcs/ft_strnew.c \
			srcs/ft_strdel.c \
			srcs/ft_strclr.c \
			srcs/ft_strchr.c \
			srcs/ft_strrchr.c \
			srcs/ft_strmap.c \
			srcs/ft_strmapi.c \
			srcs/ft_striter.c \
			srcs/ft_striteri.c \
			srcs/ft_str_is_alpha.c \
			srcs/ft_str_is_lowercase.c \
			srcs/ft_str_is_uppercase.c \
			srcs/ft_str_is_numeric.c \
			srcs/ft_str_is_printable.c \
			srcs/ft_strcapitalize.c \
			srcs/ft_strlowcase.c \
			srcs/ft_strupcase.c \
			srcs/ft_strcpy.c \
			srcs/ft_strncpy.c \
			srcs/ft_strlcpy.c \
			srcs/ft_strcat.c \
			srcs/ft_strncat.c \
			srcs/ft_strlcat.c \
			srcs/ft_strstr.c \
			srcs/ft_strnstr.c \
			srcs/ft_atoi.c \
			srcs/ft_itoa.c \
			srcs/ft_ltoa.c \
			srcs/ft_lltoa.c \
			srcs/ft_itoa_base.c \
			srcs/ft_ultoa_base.c \
			srcs/ft_ulltoa_base.c \
			srcs/ft_memchr.c \
			srcs/ft_memcmp.c \
			srcs/ft_calloc.c \
			srcs/ft_strdup.c \
			srcs/ft_substr.c \
			srcs/ft_strjoin.c \
			srcs/ft_str_del_char.c \
			srcs/ft_strtrim.c \
			srcs/ft_split.c \
			srcs/ft_index.c \
			srcs/ft_lstnew_bonus.c \
			srcs/ft_lstadd_front_bonus.c \
			srcs/ft_lstsize_bonus.c \
			srcs/ft_lstlast_bonus.c \
			srcs/ft_lstadd_back_bonus.c \
			srcs/ft_lstdelone_bonus.c \
			srcs/ft_lstclear_bonus.c \
			srcs/ft_lstiter_bonus.c \
			srcs/ft_lstmap_bonus.c \
			srcs/ft_list_sort.c \
			srcs/ft_list_remove_if.c \
			srcs/ft_printf/srcs/fct_utils.c \
			srcs/ft_printf/srcs/ft_printf.c \
			srcs/ft_printf/srcs/print_fct_hexa.c \
			srcs/ft_printf/srcs/print_fct_hexa_ll.c \
			srcs/ft_printf/srcs/print_fct_longlong.c \
			srcs/ft_printf/srcs/print_fct_ulong.c \
			srcs/ft_printf/srcs/utils.c \
			srcs/ft_printf/srcs/fmt_parser.c \
			srcs/ft_printf/srcs/print_fct.c \
			srcs/ft_printf/srcs/print_fct_hexa_l.c \
			srcs/ft_printf/srcs/print_fct_long.c \
			srcs/ft_printf/srcs/print_fct_u.c \
			srcs/ft_printf/srcs/print_fct_ulonglong.c \
			srcs/get_next_line/get_next_line.c \


OBJS =		$(SRCS:.c=.o)
HEADERS = 	includes/libft.h

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror
MAIN =		main_exec
DEBUG =		-Wall -Wextra -Werror -g3 -fsanitize=address
LINUX =		-Wall -Wextra

CURRENT_FLAGS = $(CFLAGS)

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

.c.o:
			$(CC) $(CURRENT_FLAGS) -c -I $(HEADERS) $< -o $(<:.c=.o)

clean:
			rm -f $(OBJS) $(OBJS_B)

fclean:		clean mclean
			rm -f $(NAME)

re:			fclean all

norm:
			norminette $(SRCS) $(SRCS_B) $(HEADERS) 

$(MAIN):	main.c $(NAME)
			$(CC) $(CURRENT_FLAGS) main.c $(NAME) -o $(MAIN)

mclean:
			rm -f $(MAIN)

main: 		mclean all $(MAIN)
			./$(MAIN)

.PHONY: 	all re norm main clean fclean mclean

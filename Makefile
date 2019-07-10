# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oorlov <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/19 01:12:56 by oorlov            #+#    #+#              #
#    Updated: 2019/05/19 01:13:09 by oorlov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

NAME = ft_ls

HEADER = include/ft_ls.h

SRCS = srcs/ft_ls.c \
		srcs/keys.c \
		srcs/open_dir.c \
		srcs/print_l.c \
		srcs/sort_params.c \
		srcs/subfunction.c \
		srcs/search_file.c

all : $(NAME)

$(NAME):
	gcc $(CFLAGS) $(SRCS) -I $(HEADER) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all
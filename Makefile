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

LIB = ft_ls.a

HEADER = include/ft_ls.h

SRCS = srcs/ft_ls.c \
		srcs/keys.c \
		srcs/open_dir.c \
		srcs/print_l.c \
		srcs/sort_params.c \
		srcs/subfunction.c \
		srcs/search_file.c \
		srcs/subf2.c \
		srcs/ft_strlen.c \
		srcs/dir_err.c \
		srcs/recursion.c \
		srcs/file_struct.c \
		srcs/type_file.c

OBJ = ft_ls.o \
		keys.o \
		open_dir.o \
		print_l.o \
		sort_params.o \
		subfunction.o \
		search_file.o \
		subf2.o \
		ft_strlen.o \
		dir_err.o \
		recursion.o \
		file_struct.o \
		type_file.o

all : $(NAME)

$(NAME):
	gcc -c $(CFLAGS) $(SRCS) $(HEADER)
	gcc $(CFLAGS) $(SRCS) -I $(HEADER) -o $(NAME)
	ar rc $(LIB) $(OBJ)
	@rm -f ./include/ft_ls.h.gch

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB)

re: fclean all
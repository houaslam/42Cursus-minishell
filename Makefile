# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aatki <aatki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 22:26:16 by aatki             #+#    #+#              #
#    Updated: 2023/04/30 13:50:36 by aatki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = execution

NAMEB = execution.a

LIBFT =  ./libft/ft_atoi.c \
		./libft/ft_bzero.c \
		./libft/ft_calloc.c \
		./libft/ft_isalnum.c \
		./libft/ft_isalpha.c \
		./libft/ft_isascii.c \
		./libft/ft_isdigit.c \
		./libft/ft_isprint.c \
		./libft/ft_itoa.c \
		./libft/ft_memchr.c \
		./libft/ft_memcmp.c \
		./libft/ft_memcpy.c \
		./libft/ft_memmove.c \
		./libft/ft_memset.c \
		./libft/ft_putchar_fd.c \
		./libft/ft_putendl_fd.c \
		./libft/ft_putnbr_fd.c \
		./libft/ft_putstr_fd.c \
		./libft/ft_split.c \
		./libft/ft_strchr.c \
		./libft/ft_strdup.c \
		./libft/ft_striteri.c \
		./libft/ft_strjoin.c \
		./libft/ft_strlcat.c \
		./libft/ft_strlcpy.c \
		./libft/ft_strlen.c \
		./libft/ft_strmapi.c \
		./libft/ft_strncmp.c \
		./libft/ft_strnstr.c \
		./libft/ft_strrchr.c \
		./libft/ft_strtrim.c \
		./libft/ft_substr.c \
		./libft/ft_tolower.c \
		./libft/ft_toupper.c \
		./libft/ft_strcmp.c \
		./libft/ft_strcpy.c

BUILTINS = ./builtins/utils.c\
			./builtins/cd.c\
			./builtins/echo.c\
			./builtins/env.c\
			./builtins/exit.c\
			./builtins/export.c\
			./builtins/pwd.c\
			./builtins/unset.c\
			./builtins/export_utils.c

PIPEX =./pipex/pipex_bonus.c\
		./pipex/pipex_utils_bonus.c\
		./pipex/ft_split_bonus.c\
		./pipex/here_doc.c\
		./pipex/get_next_line.c\
		./pipex/get_next_line_utils.c\
		./pipex/open_files.c

OBJ1 = ${BUILTINS:.c=.o}

OBJ2 = ${PIPEX:.c=.o}

SRC= ${PIPEX} ${BUILTINS} ${LIBFT}

OBJ = ${SRC.c=.o}

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address 

all: ${NAME} biblio

${NAME}: ${OBJ} main.c
	gcc ${CFLAGS}  main.c ${OBJ} -o ${NAME}

biblio: ${NAMEB}

${NAMEB}: ${OBJ}
	ar rcs ${NAMEB} ${OBJ}

clean:
	rm -f ${OBJ1} ${OBJ2}

fclean: clean
	rm -f ${NAME} ${NAMEB}

re: fclean all

git:
	git add . && git commit -m "execution" && git push origin aicha
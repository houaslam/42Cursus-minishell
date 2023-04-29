# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aatki <aatki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 22:47:05 by houaslam          #+#    #+#              #
#    Updated: 2023/04/29 15:54:19 by aatki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

LIBFT =  ./execution/libft/ft_atoi.c \
		./execution/libft/ft_bzero.c \
		./execution/libft/ft_calloc.c \
		./execution/libft/ft_isalnum.c \
		./execution/libft/ft_isalpha.c \
		./execution/libft/ft_isascii.c \
		./execution/libft/ft_isdigit.c \
		./execution/libft/ft_isprint.c \
		./execution/libft/ft_itoa.c \
		./execution/libft/ft_memchr.c \
		./execution/libft/ft_memcmp.c \
		./execution/libft/ft_memcpy.c \
		./execution/libft/ft_memmove.c \
		./execution/libft/ft_memset.c \
		./execution/libft/ft_putchar_fd.c \
		./execution/libft/ft_putendl_fd.c \
		./execution/libft/ft_putnbr_fd.c \
		./execution/libft/ft_putstr_fd.c \
		./execution/libft/ft_split.c \
		./execution/libft/ft_strchr.c \
		./execution/libft/ft_strdup.c \
		./execution/libft/ft_striteri.c \
		./execution/libft/ft_strjoin.c \
		./execution/libft/ft_strlcat.c \
		./execution/libft/ft_strlcpy.c \
		./execution/libft/ft_strlen.c \
		./execution/libft/ft_strmapi.c \
		./execution/libft/ft_strncmp.c \
		./execution/libft/ft_strnstr.c \
		./execution/libft/ft_strrchr.c \
		./execution/libft/ft_strtrim.c \
		./execution/libft/ft_substr.c \
		./execution/libft/ft_tolower.c \
		./execution/libft/ft_toupper.c \
		./execution/libft/ft_strcmp.c \
		./execution/libft/ft_strcpy.c

BUILTINS = ./execution/builtins/utils.c\
			./execution/builtins/cd.c\
			./execution/builtins/echo.c\
			./execution/builtins/env.c\
			./execution/builtins/exit.c\
			./execution/builtins/export.c\
			./execution/builtins/pwd.c\
			./execution/builtins/unset.c\
			./execution/builtins/export_utils.c

PIPEX =./execution/pipex/pipex_bonus.c\
		./execution/pipex/pipex_utils_bonus.c\
		./execution/pipex/ft_split_bonus.c\
		./execution/pipex/here_doc.c\
		./execution/pipex/get_next_line.c\
		./execution/pipex/get_next_line_utils.c\
		./execution/pipex/open_files.c

SRC =  main.c \
		creat_env.c \
		libft_bonus/env_linked_list.c \
		libft_bonus/exec_linked_list.c \
		libft_bonus/file_linked_list.c \
		tokens_string.c \
		tokens_spec_char.c \
		outils.c \
		ft_isstring.c\
		transmetter.c

SRCS= ${SRC} ${PIPEX} ${BUILTINS} ${LIBFT}

all : ${NAME}

OBJ = ${SRCS:.c=.o}
B_OBJ = ${B_SRCS:.c=.o}


${NAME} : ${SRCS}
	cc $(CFLAGS) ${SRCS}  -o ${NAME} -L/usr/local/lib -lreadline

clean :
	rm -f ${OBJ}

push :
	git add .
	git commit -m minishell
	git push origin hajar

fclean : clean
	rm -f $(NAME)

re: fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aatki <aatki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 22:47:05 by houaslam          #+#    #+#              #
#    Updated: 2023/04/29 16:18:33 by aatki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

LIBFT =  ./executionn/libft/ft_atoi.c \
		./executionn/libft/ft_bzero.c \
		./executionn/libft/ft_calloc.c \
		./executionn/libft/ft_isalnum.c \
		./executionn/libft/ft_isalpha.c \
		./executionn/libft/ft_isascii.c \
		./executionn/libft/ft_isdigit.c \
		./executionn/libft/ft_isprint.c \
		./executionn/libft/ft_itoa.c \
		./executionn/libft/ft_memchr.c \
		./executionn/libft/ft_memcmp.c \
		./executionn/libft/ft_memcpy.c \
		./executionn/libft/ft_memmove.c \
		./executionn/libft/ft_memset.c \
		./executionn/libft/ft_putchar_fd.c \
		./executionn/libft/ft_putendl_fd.c \
		./executionn/libft/ft_putnbr_fd.c \
		./executionn/libft/ft_putstr_fd.c \
		./executionn/libft/ft_split.c \
		./executionn/libft/ft_strchr.c \
		./executionn/libft/ft_strdup.c \
		./executionn/libft/ft_striteri.c \
		./executionn/libft/ft_strjoin.c \
		./executionn/libft/ft_strlcat.c \
		./executionn/libft/ft_strlcpy.c \
		./executionn/libft/ft_strlen.c \
		./executionn/libft/ft_strmapi.c \
		./executionn/libft/ft_strncmp.c \
		./executionn/libft/ft_strnstr.c \
		./executionn/libft/ft_strrchr.c \
		./executionn/libft/ft_strtrim.c \
		./executionn/libft/ft_substr.c \
		./executionn/libft/ft_tolower.c \
		./executionn/libft/ft_toupper.c \
		./executionn/libft/ft_strcmp.c \
		./executionn/libft/ft_strcpy.c

BUILTINS = ./executionn/builtins/utils.c\
			./executionn/builtins/cd.c\
			./executionn/builtins/echo.c\
			./executionn/builtins/env.c\
			./executionn/builtins/exit.c\
			./executionn/builtins/export.c\
			./executionn/builtins/pwd.c\
			./executionn/builtins/unset.c\
			./executionn/builtins/export_utils.c

PIPEX =./executionn/pipex/pipex_bonus.c\
		./executionn/pipex/pipex_utils_bonus.c\
		./executionn/pipex/ft_split_bonus.c\
		./executionn/pipex/here_doc.c\
		./executionn/pipex/get_next_line.c\
		./executionn/pipex/get_next_line_utils.c\
		./executionn/pipex/open_files.c

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
	git push origin master

fclean : clean
	rm -f $(NAME)

re: fclean all
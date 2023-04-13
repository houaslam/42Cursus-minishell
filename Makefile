# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 22:47:05 by houaslam          #+#    #+#              #
#    Updated: 2023/04/11 16:07:38 by houaslam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address 

SRCS =  main.c \
		creat_env.c \
		libft_bonus/env_linked_list.c \
		libft_bonus/exec_linked_list.c \
		tokens_string.c \
		tokens_spec_char.c \
		outils.c
		

all : ${NAME}

OBJ = ${SRCS:.c=.o}
B_OBJ = ${B_SRCS:.c=.o}


${NAME} : ${OBJ}
	cc $(CFLAGS)  libft/libft.a ${OBJ}  -o ${NAME} -L/usr/local/lib -lreadline

clean :
	rm -f ${OBJ}

push :
	git add .
	git commit -m minishell
	git push origin hajar

fclean : clean
	rm -f $(NAME)

re: fclean all
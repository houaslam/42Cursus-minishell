# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 22:47:05 by houaslam          #+#    #+#              #
#    Updated: 2023/04/03 15:57:30 by houaslam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address 

SRCS =  main.c \
		creat_env.c \
		libft_bonus/env_linked_list.c \
		libft_bonus/exec_linked_list.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		tokens.c 
		

all : ${NAME}

OBJ = ${SRCS:.c=.o}
B_OBJ = ${B_SRCS:.c=.o}


${NAME} : ${OBJ}
	cc $(CFLAGS)  libft_/libft.a ${OBJ} -o ${NAME}

clean :
	rm -f ${OBJ}

push :
	git add .
	git commit -m minishell
	git push origin hajar

fclean : clean
	rm -f $(NAME)

re: fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 22:47:05 by houaslam          #+#    #+#              #
#    Updated: 2023/04/02 21:01:32 by houaslam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address 

SRCS =  main.c \
		creat_env.c \
		libft_bonus/libft2.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		

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
	git push

fclean : clean
	rm -f $(NAME)

re: fclean all
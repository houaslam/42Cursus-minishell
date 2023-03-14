# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 22:47:05 by houaslam          #+#    #+#              #
#    Updated: 2023/03/14 22:49:58 by houaslam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror

SRCS =  main.c

all : ${NAME}

OBJ = ${SRCS:.c=.o}
B_OBJ = ${B_SRCS:.c=.o}


${NAME} : ${OBJ}
	cc $(CFLAGS) ${OBJ} -o ${NAME}

clean :
	rm -f ${OBJ}

push :
	git add .
	git commit -m minishell
	git push

fclean : clean
	rm -f $(NAME)

re: fclean all
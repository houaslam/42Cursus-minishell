# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aatki <aatki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 17:07:21 by aatki             #+#    #+#              #
#    Updated: 2023/03/12 14:20:57 by aatki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAMEB = pipex_bonus

SRC = pipex.c\
	pipex_utils.c\
	ft_split.c

SRCB = ./bonus/pipex_bonus.c\
	./bonus/pipex_utils_bonus.c\
	./bonus/ft_split_bonus.c\
	./bonus/here_doc.c\
	./bonus/get_next_line.c\
	./bonus/get_next_line_utils.c\

OBJC = ${SRC :.c=.o}

OBJCB = ${SRCB :.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

${NAME} : ${SRC}
	${CC} ${CFLAGS}  ${SRC} -o ${NAME}

bonus : ${NAMEB}

${NAMEB} : ${SRCB}
	${CC} ${CFLAGS}  ${SRCB} -o ${NAMEB}

clean :
	rm -rf ${OBJC} ${OBJCB}

fclean: clean
	rm -rf ${NAME} ${NAMEB}

re : fclean all

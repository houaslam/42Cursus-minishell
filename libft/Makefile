# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aatki <aatki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/23 21:13:19 by aatki             #+#    #+#              #
#    Updated: 2022/10/27 23:35:30 by aatki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_calloc.c ft_isalpha.c ft_isdigit.c ft_memchr.c ft_memcpy.c \
	ft_memset.c ft_strdup.c ft_strlcpy.c ft_strncmp.c ft_strrchr.c ft_toupper.c \
	ft_bzero.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memcmp.c ft_memmove.c ft_strchr.c \
	ft_strlcat.c ft_strlen.c ft_strnstr.c ft_tolower.c ft_substr.c ft_strtrim.c ft_split.c \
	ft_strjoin.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c

BSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
	ft_lstiter_bonus.c ft_lstadd_back_bonus.c ft_lstmap_bonus.c

AR = ar -rc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

CC = cc

OBJS = ${SRC:.c=.o}

BOBJ = ${BSRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}

bonus: ${BOBJ} ${OBJS}

%.o : %.c
	${CC} ${CFLAGS} -c $<
	${AR} ${NAME} $@

clean :
	${RM} ${OBJS} ${BOBJ}

fclean : clean
	${RM} ${NAME}

re : fclean all

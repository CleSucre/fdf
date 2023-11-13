# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julthoma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 17:07:47 by julthoma          #+#    #+#              #
#    Updated: 2023/11/02 17:07:47 by julthoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(OS), Windows_NT)
	DIRSEP	= \\
	CP		= copy
	RM		= del -f
else
	DIRSEP	= /
	CP		= cp
	RM		= rm -f
endif

NAME		= fdf

SRCS		= ft_fdf.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

HEAD		= .

LIBFT_DIR	= libft

MLX_DIR		= minilibx

CFLAGS		= -Wall -Wextra -Werror -I ${HEAD}

MLX = -L ${MLX_DIR}

%.o : %.c
	${CC} ${CFLAGS} -o $@ -c $<

${NAME}: ${OBJS}
	make -C ${LIBFT_DIR}
	make -C ${MLX_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L ${LIBFT_DIR} ${MLX} -lft

all: ${NAME}

clean: 
	make -C ${LIBFT_DIR} clean
	make -C ${MLX_DIR} clean
	${RM} ${OBJS}

fclean: clean
	make -C ${LIBFT_DIR} fclean
	make -C ${MLX_DIR} clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

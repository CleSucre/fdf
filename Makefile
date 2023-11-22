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

SRCS		= main.c ft_fdf.c ft_utils.c ft_actions.c

OBJ_PATH	= obj${DIRSEP}

OBJ_NAME	= ${SRCS:%.c=%.o}

OBJS		= ${addprefix ${OBJ_PATH}, ${OBJ_NAME}}

CC			= gcc

HEAD		= .

LIBFT_DIR	= libft

MLX_DIR		= minilibx

CFLAGS		= -g -I ${HEAD}

${OBJ_PATH}%.o : %.c
	mkdir -p ${@D} 2> /dev/null || true
	${CC} ${CFLAGS} -o $@ -c $<

${NAME}: ${OBJS}
	make -C ${LIBFT_DIR}
	make -C ${MLX_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L ${LIBFT_DIR} -L ${MLX_DIR} -L ${MLX_DIR} -lft -lmlx -lXext -lX11 -lm

all: ${NAME}

clean: 
	make -C ${LIBFT_DIR} clean
	make -C ${MLX_DIR} clean
	${RM} -r ${OBJ_PATH} 2> /dev/null || true

fclean:
	make -C ${LIBFT_DIR} fclean
	make -C ${MLX_DIR} clean
	${RM} -r ${OBJ_PATH} 2> /dev/null || true
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

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

SRCS		= fdf.c

SRCS_BONUS	= fdf_bonus.c map_maker_bonus.c maker_bonus.c keymap_bonus.c destroyer_bonus.c drawer_bonus.c color_manager_bonus.c trigo_bonus.c camera_bonus.c map_bonus.c

OBJ_PATH	= obj${DIRSEP}

SRC_PATH	= src${DIRSEP}

OBJ_NAME	= ${addprefix ${SRC_PATH}, ${SRCS:%.c=%.o}}

OBJS		= ${addprefix ${OBJ_PATH}, ${OBJ_NAME}}

OBJ_NAME_BONUS	= ${addprefix ${SRC_PATH}, ${SRCS_BONUS:%.c=%.o}}

OBJS_BONUS	= ${addprefix ${OBJ_PATH}, ${OBJ_NAME_BONUS}}

CC			= gcc

HEAD		= src

LIBFT_DIR	= libft

MLX_DIR		= minilibx

CFLAGS		= -O2 -I ${HEAD} -Wall -Wextra -Werror

${OBJ_PATH}%.o : %.c
	mkdir -p ${@D} 2> /dev/null || true
	${CC} ${CFLAGS} -o $@ -c $<

${NAME}: ${OBJS}
	make -C ${LIBFT_DIR}
	make -C ${MLX_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L ${LIBFT_DIR} -L ${MLX_DIR} -lft -lmlx -lXext -lX11 -lm

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
	${RM} ${NAME}_bonus

bonus: ${OBJS_BONUS}
	make -C ${LIBFT_DIR}
	make -C ${MLX_DIR}
	${CC} ${CFLAGS} -o ${NAME}_bonus ${OBJS_BONUS} -L ${LIBFT_DIR} -L ${MLX_DIR} -lft -lmlx -lXext -lX11 -lm

re: fclean all

.PHONY: all clean fclean re bonus

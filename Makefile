# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 16:04:36 by acaillea          #+#    #+#              #
#    Updated: 2022/11/02 16:15:41 by acaillea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include ./Includes/colors.mk

# ************************************************************************* #
#								Name & Commands								#
# ************************************************************************* #

# -----------	Name ---------------- #

NAME		=	cub3D
NAME_BONUS	=	cub3D_bonus

# -----------	Sources ------------- #

SRCS_DIR	=	./Sources/

SRCS		=	exit.c					\
				exit_utils.c			\
				ft_atoi.c				\
				ft_split.c				\
				ft_strtrim.c			\
				get_next_line1.c		\
				get_next_line2.c		\
				hook.c					\
				initDrawing.c			\
				initWalls.c				\
				libft1.c				\
				libft2.c				\
				malloc.c				\
				movePOV.c				\
				movement.c				\
				raycast.c				\
				raycast_utils.c			\
				read_config1.c			\
				read_config2.c			\
				read_map1.c				\
				read_map2.c

SRCS_MAIN	=	main.c

SRCS_BONUS	=	main_bonus.c			\
				mouse_hook_bonus.c

# -----------	Includes ------------ #

INC			=	./Includes/main.h

# -----------	Objects ------------- #

OBJS_DIR	=	./Objects/
OBJS		=	${addprefix ${OBJS_DIR}, ${SRCS:%.c=%.o}}
OBJS_MAIN	=	${addprefix ${OBJS_DIR}, ${SRCS_MAIN:%.c=%.o}}
OBJS_BONUS	=	${addprefix ${OBJS_DIR}, ${SRCS_BONUS:%.c=%.o}}
OBJS_FIL	= 	object_file

# -----------	Flags --------------- #

CC			=	gcc
MK			=	mkdir -p
CFLAGS		=	-Wall -Werror -Wextra

# -----------	MLX ----------------- #

MLX			= 	-lmlx -framework OpenGL -framework AppKit
# MLX		= 	-L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz --> Compilation with MLX files
# MLX		= 	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz --> Compilation with Linus

# -----------	Fonctions ----------- #

RM			= 	/bin/rm -rf
VEL			= 	sleep
PRI			= 	printf

# ************************************************************************* #
#							Rules & Compilation								#
# ************************************************************************* #


# ---------------------------------- #
# 				Objects 			 #
# ---------------------------------- #

${OBJS_DIR}%.o:${SRCS_DIR}%.c
	@${CC} ${CFLAGS} -I ${INC} -Imlx -c $< -o $@
	@${PRI} "${C_MAG}	Compiling cub3D:	\
	${C_CYAN}[${C_ORANGE}$<${C_CYAN}] $(C_RESET) $(L_CLEAR)${C_DEFAUT}\r"
	@${VEL} 0.1
	@printf "$(L_CLEAR)\r"

all : ${OBJS_FIL} ${NAME}

${OBJS_FIL} :
	@${MK} ${OBJS_DIR}

${NAME}: ${OBJS_MAIN} ${OBJS}
	@${CC} ${CFLAGS} ${OBJS_MAIN} ${OBJS} ${MLX} -o ${NAME}
	@${PRI} "\n${C_CYAN}[${C_GREEN}✔︎${C_CYAN}]	\
	${C_GREEN}$@ 🧊🧊🧊 ${C_GREEN}Successfully built${C_DEFAUT}\n\n"

${NAME_BONUS}: ${OBJS_BONUS} ${OBJS}
	@${CC} ${CFLAGS} ${MLX} ${OBJS_BONUS} ${OBJS} -o ${NAME_BONUS}
	@${PRI} "\n${C_CYAN}[${C_GREEN}✔︎${C_CYAN}]	\
	${C_GREEN}$@ 🧊🧊🧊 ${C_GREEN}Successfully built${C_DEFAUT}\n\n"

# ---------------------------------- #
# 				Bonus	 			 #
# ---------------------------------- #

bonus :	${OBJS_FIL} ${NAME_BONUS}

# ---------------------------------- #
# 				Clean	 			 #
# ---------------------------------- #

clean :
	@${RM} ${OBJS_DIR}
	@${PRI} "${C_CYAN}[${C_GREEN}✔︎${C_CYAN}]	${C_RED}Files deleted${C_DEFAUT}\n"

fclean : clean
	@${RM} ${NAME}
	@${RM} ${NAME_BONUS}
	@${PRI} "${C_CYAN}[${C_GREEN}✔︎${C_CYAN}]	${C_RED}Exe & mlx files deleted${C_DEFAUT}\n"

# ---------------------------------- #
# 				Re		 			 #
# ---------------------------------- #

re : fclean all

# ----------------------------------- #

.PHONY : all bonus clean fclean re

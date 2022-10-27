    # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 16:04:36 by acaillea          #+#    #+#              #
#    Updated: 2022/10/17 17:36:46 by acaillea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include ./Includes/colors.mk

# ************************************************************************* #
#								Name & Commands								#
# ************************************************************************* #

# -----------	Name ---------------- #

NAME		=	Cub3D
NAME_BONUS	=	Cub3D_Bonus

# -----------	Sources ------------- #

SRCS_DIR	=	./Sources/

SRCS		=	raycast.c				\
				utils.c					\
				exit.c					\
				malloc.c				\
				initDrawing.c			\
				raycast_utils.c			\
				hook.c					\
				moovePOV.c				\
				mouvement.c				\
				read_config.c			\
				read_map.c				\
				ft_atoi.c				\
				ft_split.c				\
				libft.c					\
				initWalls.c				\
				ft_strtrim.c			\
				get_next_line.c			\
				mini_map_bonus.c

SRCS_MAIN	=	main.c

SRCS_BONUS	=	main_bonus.c			\
#				mini_map_bonus.c

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
MK			=	mkdir
CFLAGS		=	-Wall -Werror -Wextra

# -----------	MLX ----------------- #

MLX			= 	-lmlx -framework OpenGL -framework AppKit

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
	@${PRI} "${C_MAG}	Compiling Cub3D:	\
	${C_CYAN}[${C_ORANGE}$<${C_CYAN}] $(C_RESET) $(L_CLEAR)${C_DEFAUT}\r"
#	 @${VEL} 0.5
	@printf "$(L_CLEAR)\r"

all : ${OBJS_FIL} ${NAME}

${OBJS_FIL} :
	@${MK} ${OBJS_DIR}

${NAME}: ${OBJS_MAIN} ${OBJS}
	@${CC} ${CFLAGS} ${MLX} ${OBJS_MAIN} ${OBJS} -o ${NAME}
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

.PHONY : all clean fclean re


# rajouter suppression object MLX
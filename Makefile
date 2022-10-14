# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 16:04:36 by acaillea          #+#    #+#              #
#    Updated: 2022/10/14 11:57:07 by hcremers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include ./Includes/colors.mk

# ************************************************************************* #
#								Name & Commands								#
# ************************************************************************* #

# -----------	Name ---------------- #

NAME		=	cub3d

# -----------	Sources ------------- #

SRCS_DIR	=	./Sources/
SRCS		=	recastSage.c

# -----------	Includes ------------ #

INC			=	./Includes/main.h

# -----------	Objects ------------- #

OBJS_DIR	=	./Objects/
OBJS		=	${addprefix ${OBJS_DIR}, ${SRCS:%.c=%.o}}
OBJS_FIL	= 	object_file

# -----------	Flags --------------- #

CC			=	gcc
MK			=	mkdir
CFLAGS		=	-Wall -Werror -Wextra

# -----------	MLX ----------------- #

MMLX		= 	make -s -C 
MLX			= 	-L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz

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
	@${PRI} "${C_MAG}	Compiling cub3d:	\
	${C_CYAN}[${C_ORANGE}$<${C_CYAN}] $(C_RESET) $(L_CLEAR)${C_DEFAUT}\r"
#	 @${VEL} 0.5
	@printf "$(L_CLEAR)\r"

all : ${OBJS_FIL} ${NAME}

${OBJS_FIL} :
	@${MK} ${OBJS_DIR}

${NAME}: ${OBJS}
	@${MMLX} ./mlx
	@${CC} ${CFLAGS} ${MLX} ${OBJS} -o ${NAME}
	@${PRI} "\n${C_CYAN}[${C_GREEN}✔︎${C_CYAN}]	\
	${C_GREEN}$@ 🧊🧊🧊 ${C_GREEN}Successfully built${C_DEFAUT}\n\n"

# ---------------------------------- #
# 				Clean	 			 #
# ---------------------------------- #

clean :
	@${RM} ${OBJS_DIR}
	@${PRI} "${C_CYAN}[${C_GREEN}✔︎${C_CYAN}]	${C_RED}Files deleted${C_DEFAUT}\n"

fclean : clean
	@${RM} ${NAME}
	@${PRI} "${C_CYAN}[${C_GREEN}✔︎${C_CYAN}]	${C_RED}Exe deleted${C_DEFAUT}\n"

# ---------------------------------- #
# 				Re		 			 #
# ---------------------------------- #

re : fclean all

# ----------------------------------- #

.PHONY : all clean fclean re


# rajouter suppression object MLX
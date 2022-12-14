# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 15:12:04 by acaillea          #+#    #+#              #
#    Updated: 2022/11/10 21:01:43 by hcremers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		= main.c

OBJS		= $(addprefix $(OBJDIR), $(SRCS:.c=.o))
OBJDIR		= Objects/

CC			= gcc
RM			= rm -f
MKDIR		= mkdir

LIBDIR		= Sources/
LIB			= $(LIBDIR)libsrcs.a

MLX			= -lmlx -framework OpenGL -framework AppKit							# MacOS
# MLX			= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz # Linux

CFLAGS		= -Wall -Wextra -Werror

###############################################################################

$(OBJDIR)%.o:	%.c
				$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJDIR), $(<:.c=.o))

all:			$(NAME)

$(NAME):		$(OBJS)
				make -C $(LIBDIR)
				$(CC) $(CFLAGS) $(OBJS) $(LIB) $(MLX) -o $(NAME)

$(OBJS):		| $(OBJDIR)

$(OBJDIR):		
				$(MKDIR) $(OBJDIR)

clean:
				make clean -C $(LIBDIR)
				$(RM) $(wildcard *.o)
				$(RM) -r $(OBJDIR)

fclean:			clean
				make fclean -C $(LIBDIR)
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re

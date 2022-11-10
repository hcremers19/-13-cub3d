# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 15:12:04 by acaillea          #+#    #+#              #
#    Updated: 2022/11/10 20:54:53 by hcremers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libsrcs.a

SRCS	= $(wildcard *.c)

OBJS	= $(addprefix $(OBJDIR), $(SRCS:.c=.o))
OBJDIR	= objs/

CC		= gcc
RM		= rm -f
MKDIR	= mkdir

CFLAGS	= -Wall -Wextra -Werror

###############################################################################

$(OBJDIR)%.o:	%.c
				$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJDIR), $(<:.c=.o))

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS) $(LIB)
				ranlib $(NAME)

$(OBJS):		| $(OBJDIR)

$(OBJDIR):		
				$(MKDIR) $(OBJDIR)

clean:
				$(RM) $(wildcard *.o)
				$(RM) -r $(OBJDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 15:52:58 by mdelforg          #+#    #+#              #
#    Updated: 2022/05/29 10:03:24 by mdelforg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/main.c \
	   srcs/routine.c \
	   srcs/utils.c \
	   srcs/error_msg.c \
	   srcs/libc.c \

OBJS = $(SRCS:.c=.o)

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

$(NAME):	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

exe:		all clean

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.PHONY:		exe clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 15:39:10 by user42            #+#    #+#              #
#    Updated: 2021/02/01 18:30:00 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

CFLAGS	= -Werror -Wextra -Wall -I.
CFLAGS	+= -fsanitize=address
CFLAGS 	+= -g3

ifeq ("$(UNAME)", Darwin)
	CC		=	gcc
else
	CC		=	clang
endif

SRCS = 	main.c \
		philo_two.c \
		init.c \
		destructor.c \
		print.c \
		lib.c

OBJS = $(SRCS:%.c=%.o)

all :	$(NAME)

$(NAME) : philo.h $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

%.o : %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 15:39:10 by user42            #+#    #+#              #
#    Updated: 2021/02/16 09:59:13 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

CFLAGS += -Werror -Wextra -Wall -I.
#CFLAGS += -O
#CFLAGS	+= -fsanitize=thread
#CFLAGS	+= -fsanitize=address

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
	CC		=	gcc
else
	CC		=	clang
endif

SRCS = 	main.c \
		philo_two.c \
		philo_action.c \
		init.c \
		destructor.c \
		print.c \
		lib.c \
		lib2.c

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
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plee <plee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 13:20:26 by plee              #+#    #+#              #
#    Updated: 2021/11/08 14:39:20 by plee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDE := -I./includes
.SUFFIXES : .c .o

SRCS := main.c utils.c dine.c
OBJ_DIR := ./obj
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

$(OBJ_DIR)/%.o : ./%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
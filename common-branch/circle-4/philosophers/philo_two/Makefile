# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 16:41:02 by ablanc            #+#    #+#              #
#    Updated: 2020/10/17 19:16:28 by ablanc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = ./main.c\
	./parsing.c\
	./actions.c\
	./init.c\
	./test.c\
	./time.c\
	./helpers.c\
	./helpers_2.c\
	./sem.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ -l pthread

%.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re

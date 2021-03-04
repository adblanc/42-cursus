# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/21 15:31:21 by ablanc            #+#    #+#              #
#    Updated: 2020/10/21 16:12:04 by ablanc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = ./main.c\
	./parsing.c\
	./actions.c\
	./init.c\
	./test.c\
	./sem.c\
	./helpers.c\
	./helpers_2.c\
	./time.c

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

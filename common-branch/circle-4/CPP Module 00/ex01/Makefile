# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/16 10:23:17 by ablanc            #+#    #+#              #
#    Updated: 2019/12/16 15:16:09 by ablanc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = annul

CC = g++

FLAGS = -Wall -Wextra -Werror

SRC =	./main.cpp\
		./Contact.cpp\

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re



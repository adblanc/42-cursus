# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrien <adrien@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/14 10:47:04 by adrien            #+#    #+#              #
#    Updated: 2020/01/14 17:52:07 by adrien           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = type

CC = g++

FLAGS = -Wall -Wextra -Werror

SRC =	./main.cpp\
		./Base.cpp\
		./A.cpp\
		./B.cpp\
		./C.cpp

OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@

%.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/27 12:03:41 by adrien            #+#    #+#              #
#    Updated: 2020/10/24 15:55:40 by fcadet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_containers

FLAGS = -Wall -Wextra -Werror
ACTUAL_CC = clang++

V = 0
CC_0 = @echo "Compiling $<..."; $(ACTUAL_CC)
CC_1 = $(ACTUAL_CC)
CC = $(CC_$(V))

SRC = ./src/main.cpp\
		./src/test-utils/testUtils.cpp\
		./src/shared/tests/rbt.test.cpp\
		./src/shared/tests/iterators.test.cpp\
		./src/multiset/tests/multiset.test.cpp\
		./src/set/tests/set.test.cpp\
		./src/multimap/tests/multimap.test.cpp\
		./src/map/tests/map.test.cpp\
		./src/vector/tests/vector.test.cpp\
		./src/stack/tests/stack.test.cpp\
		./src/queue/tests/queue.test.cpp\
		./src/shared/tests/pair.test.cpp\
		./src/list/tests/list.test.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

runTest: all
	clear
	./$(NAME)

test: runTest fclean

.PHONY: clean all fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/23 15:57:17 by ablanc            #+#    #+#              #
#    Updated: 2019/12/16 09:14:39 by ablanc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
#FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra
#FLAGS = -Wall -Wextra
FLAGS = -Wall -Wextra -Werror

ROOT_DIR = ./

INCLUDES_DIR = $(ROOT_DIR)includes/

BUILTINS_DIR = $(ROOT_DIR)builtins/
CD_DIR = $(BUILTINS_DIR)cd/
ECHO_DIR = $(BUILTINS_DIR)echo/
ENV_DIR = $(BUILTINS_DIR)env/
EXIT_DIR = $(BUILTINS_DIR)exit/
EXPORT_DIR = $(BUILTINS_DIR)export/
PWD_DIR = $(BUILTINS_DIR)pwd/
UNSET_DIR = $(BUILTINS_DIR)unset/

MINISHELL_DIR = $(ROOT_DIR)shell/
PIPES_DIR = $(ROOT_DIR)pipes/
PROCESSES_DIR = $(ROOT_DIR)processes/
REDIRECTIONS_DIR = $(ROOT_DIR)redirections/
UTILS_DIR = $(ROOT_DIR)utils/
CUT_CMDS_DIR = $(ROOT_DIR)cut_cmds/


SRC = $(MINISHELL_DIR)minishell_1.c\
	$(MINISHELL_DIR)minishell_2.c\
	$(MINISHELL_DIR)minishell_3.c\
	$(MINISHELL_DIR)minishell_utils.c\
	$(REDIRECTIONS_DIR)redirection.c\
	$(REDIRECTIONS_DIR)redirection_utils.c\
	$(PIPES_DIR)pipes.c\
	$(PROCESSES_DIR)process.c\
	$(PROCESSES_DIR)process_utils.c\
	$(ECHO_DIR)echo.c\
	$(CD_DIR)cd_1.c\
	$(CD_DIR)cd_2.c\
	$(PWD_DIR)pwd.c\
	$(EXPORT_DIR)export.c\
	$(UNSET_DIR)unset.c\
	$(ENV_DIR)env_1.c\
	$(ENV_DIR)env_2.c\
	$(ENV_DIR)env_3.c\
	$(ENV_DIR)env_4.c\
	$(ENV_DIR)env_5.c\
	$(ENV_DIR)env_utils.c\
	$(EXIT_DIR)exit.c\
	$(CUT_CMDS_DIR)cut_cmds.c\
	$(CUT_CMDS_DIR)cut_cmds_utils.c\
	$(CUT_CMDS_DIR)cut_cmds_utils_2.c\
	$(UTILS_DIR)utils_1.c\
	$(UTILS_DIR)utils_2.c\
	$(UTILS_DIR)utils_3.c\
	$(UTILS_DIR)utils_4.c\
	$(UTILS_DIR)ft_split.c\
	$(UTILS_DIR)ft_itoa.c\
	$(UTILS_DIR)mem.c\
	$(UTILS_DIR)get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

clean:
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean all bonus fclean re

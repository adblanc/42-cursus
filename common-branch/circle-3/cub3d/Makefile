# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/26 08:25:13 by ablanc            #+#    #+#              #
#    Updated: 2019/11/14 17:59:19 by ablanc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

CC = gcc

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Wextra -Werror

ROOT_DIR = ./
MAP_DIR = map/
DRAW_DIR = draw/
KEYS_DIR = keys/
GNL_DIR = gnl/
RC_DIR = rc/
HELPERS_DIR = helpers/
SPRITES_DIR = sprites/
BONUS_DIR = bonus/


SRC = $(MAP_DIR)ft_check_file.c\
		$(MAP_DIR)ft_check_ids_1.c\
		$(MAP_DIR)ft_check_ids_2.c\
		$(MAP_DIR)ft_check_map.c\
		$(MAP_DIR)ft_set_player_pos.c\
		$(MAP_DIR)ft_trim_map.c\
		$(DRAW_DIR)draw_1.c\
		$(DRAW_DIR)draw_2.c\
		$(GNL_DIR)get_next_line.c\
		$(GNL_DIR)get_next_line_utils.c\
		$(KEYS_DIR)keys_1.c\
		$(KEYS_DIR)keys_2.c\
		$(RC_DIR)rc_0.c\
		$(RC_DIR)rc_1.c\
		$(RC_DIR)rc_2.c\
		$(RC_DIR)rc_3.c\
		$(SPRITES_DIR)sprites_1.c\
		$(SPRITES_DIR)sprites_2.c\
		$(SPRITES_DIR)sprites_3.c\
		$(SPRITES_DIR)sprites_4.c\
		$(ROOT_DIR)check_args.c\
		$(ROOT_DIR)cub3d.c\
		$(ROOT_DIR)error.c\
		$(ROOT_DIR)bmp.c\
		$(BONUS_DIR)health.c\
		$(BONUS_DIR)minimap.c\
		$(HELPERS_DIR)ft_atoi_length.c\
		$(HELPERS_DIR)ft_atoi.c\
		$(HELPERS_DIR)ft_in_charset.c\
		$(HELPERS_DIR)ft_isdigit.c\
		$(HELPERS_DIR)ft_putstr_fd.c\
		$(HELPERS_DIR)ft_strdup.c\
		$(HELPERS_DIR)ft_strlen.c\



OBJ = $(SRC:.c=.o)

all: $(NAME)

.PHONY: clean all bonus fclean re

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all



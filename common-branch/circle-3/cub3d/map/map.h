/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:05:56 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 16:55:33 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MAP_H

# define _MAP_H
# define INFOS_NBR 8
# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440
# include "../gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "errno.h"
# include "string.h"

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	char			orientation;
	double			mv_spd;
	double			rt_spd;
	double			camera_x;
}					t_player;

typedef struct		s_texture
{
	void			*ptr;
	int				*data;
	int				w;
	int				h;
}					t_texture;

typedef	struct		s_map
{
	int				map_index;
	int				line_nbr;
	int				column_nbr;
	char			info_count;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	char			*path_sprite;
	int				**grid;
	struct s_pos	res;
	struct s_color	floor;
	struct s_color	ceiling;
	struct s_player	p;
	int				save;
}					t_map;

typedef	struct		s_sprites
{
	double				pos_x;
	double				pos_y;
	int					sprite_num;
	double				dist;
	struct s_sprites	*next;
}					t_sprites;

typedef struct		s_raycaster
{
	void					*mlx_ptr;
	void					*win_ptr;
	void					*img_ptr;
	int						*img_data;
	int						width;
	int						height;
	int						middle_height;
	struct s_texture		textures[5];
	struct s_sprites		*sprites;
	struct s_map			*map;
	int						floor_color;
	int						ceiling_color;
	int						column;
	double					p_pos_x;
	double					p_pos_y;
	double					p_dir_x;
	double					p_dir_y;
	double					p_plane_x;
	double					p_plane_y;
	double					p_move_speed;
	double					p_rotation_speed;
	double					cam_x;
	double					ray_dir_x;
	double					ray_dir_y;
	int						map_x;
	int						map_y;
	double					side_dist_x;
	double					side_dist_y;
	double					delta_dist_x;
	double					delta_dist_y;
	double					wall_dist_perp;
	int						step_x;
	int						step_y;
	int						side;
	int						wall_height;
	int						wall_top;
	int						wall_bottom;
	double					wall_x;
	int						texture_num;
	int						texture_x;
}					t_raycaster;

typedef int	(*t_info)(char *line, t_map *);

int					free_map(t_map *map);
int					ft_end(t_map *map, int status);

/*
**	Analysis informations before map itself
*/
int					ft_check_args(int argc, char **argv, t_map *map);
int					ft_check_file(const char *path, t_map *map);
int					ft_check_n(char *line, t_map *map);
int					ft_check_so(char *line, t_map *map);
int					ft_check_w(char *line, t_map *map);
int					ft_check_e(char *line, t_map *map);
int					ft_check_r(char *line, t_map *map);
int					ft_check_sp(char *line, t_map *map);
int					ft_check_f(char *line, t_map *map);
int					ft_check_c(char *line, t_map *map);
int					ft_check_both_s(char *line, t_map *map);
char				*skip_spaces(char *s);
/*
**	Map analysis
*/
int					ft_check_map_core(char *line, t_map *map);
int					ft_check_first_last_lines(char *line, t_map *map);
int					ft_set_p_pos(t_map *map, int x, char orientation);
/*
**	Get grid trimmed
*/
int					ft_trim_map(const char *path, t_map *map);
/*
**	Start raycasting
*/
int					handle_raycasting(t_map *map);

/*
**	Error handling
*/
int					display_error(int errnum, char *error);
int					clean_exit_reading_file(int fd, char **line, int status);

/*
**	Helpers
*/
int					ft_atoi_length(const char *str);
int					ft_atoi(const char *str);
int					ft_in_charset(char c, char *charset);
int					ft_isdigit(int c);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);

#endif

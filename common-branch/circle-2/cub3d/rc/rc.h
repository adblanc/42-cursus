/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:35:12 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 15:01:15 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RC_H
# define _RC_H

# include "../minilibx/mlx.h"
# include "../map/map.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define ESCAPE 53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126

# define BYTES_PER_PIXEL     3
# define FILE_HEADER_SIZE    14
# define INFO_HEADER_SIZE    40

typedef	struct	s_direction_to_move
{
	double		dir_x;
	double		dir_y;
}				t_dir;

typedef	struct	s_z_buffer
{
	int					i;
	double				dist;
	struct s_z_buffer	*next;
}				t_z_buffer;

typedef	struct	s_sprite_proj
{
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			start_y;
	int			start_x;
	int			end_y;
	int			end_x;
}				t_sprite_proj;

typedef	struct	s_data
{
	int			bpr;
	int			size;
	int			endian;
	int			d;
	int			tex_y;
	int			tex_x;
	int			color;
}				t_data;

int				program_end(t_raycaster *rc);
int				create_bmp(t_raycaster *rc);
/*
**	Ray casting
*/
int				initialize_rc(t_raycaster *rc, t_map *map);
void			setup_ray(t_raycaster *rc);
void			get_initial_dist(t_raycaster *rc);
void			dda(t_raycaster *rc, t_map *map);
void			fire_ray(t_raycaster *rc, t_map *map);
int				cast_ray(t_raycaster *rc, t_map *map);
/*
**	Drawing
*/
int				limit(int a, int limit);
int				draw_on_image(int x, int y2, int y1, t_raycaster *rc);
int				draw_floor_and_ceiling(int x, t_raycaster *rc);
int				draw_sprites(t_raycaster *rc,
t_sprite_proj *proj, t_z_buffer *buffer);

int				initialize_textures(t_raycaster *rc, t_map *map);
int				get_texture(t_raycaster *rc);
int				rgb_to_int(int r, int g, int b);
/*
**	=== Handling keys ===
*/
int				handle_keys(int keycode, t_raycaster *rc);
void			handle_up(t_raycaster *rc, t_dir *dir, t_map *map);
void			handle_down(t_raycaster *rc, t_dir *dir, t_map *map);
void			handle_left(t_raycaster *rc, t_map *map);
void			handle_right(t_raycaster *rc, t_map *map);
/*
**	Sprites
*/
int				find_sprites(t_raycaster *rc, t_map *map);
int				store_dist(t_z_buffer **buffer, t_raycaster *rc);
void			z_buffer_clear(t_z_buffer **lst);
t_z_buffer		*find_column_wall_dist(t_z_buffer *buffer, int column);
void			lst_sprites_distance(t_raycaster *rc);
void			sort_sprites(t_raycaster *rc);
void			project_sprites(t_raycaster *rc, t_z_buffer *buffer);
int				get_data_from_sprite_texture(t_raycaster *rc);
void			sprites_clear(t_sprites **lst);

/*
**	Bonuses
*/
int				create_health_bar(t_raycaster *rc);
int				create_minimap(t_raycaster *rc);

#endif

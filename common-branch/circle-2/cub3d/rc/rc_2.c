/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:03:01 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 14:59:04 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

int			initialize_rc(t_raycaster *rc, t_map *map)
{
	rc->map = map;
	rc->width = map->res.x;
	rc->height = map->res.y;
	rc->middle_height = rc->height / 2;
	rc->img_ptr = NULL;
	rc->img_data = NULL;
	rc->mlx_ptr = NULL;
	rc->win_ptr = NULL;
	rc->sprites = NULL;
	rc->p_pos_x = map->p.pos_x;
	rc->p_pos_y = map->p.pos_y;
	rc->p_dir_x = map->p.dir_x;
	rc->p_dir_y = map->p.dir_y;
	rc->p_plane_x = map->p.plane_x;
	rc->p_plane_y = map->p.plane_y;
	rc->p_move_speed = 0.20;
	rc->p_rotation_speed = 0.20;
	rc->floor_color = rgb_to_int(map->floor.r, map->floor.g, map->floor.b);
	rc->ceiling_color = rgb_to_int(map->ceiling.r,
	map->ceiling.g, map->ceiling.b);
	return (1);
}

void		setup_ray(t_raycaster *rc)
{
	rc->cam_x = (double)2 * (double)rc->column / (double)rc->width - (double)1;
	rc->ray_dir_x = rc->p_dir_x + rc->p_plane_x * rc->cam_x;
	rc->ray_dir_y = rc->p_dir_y + rc->p_plane_y * rc->cam_x;
	rc->map_x = (int)rc->p_pos_x;
	rc->map_y = (int)rc->p_pos_y;
	rc->delta_dist_x = sqrt((double)1 +
	(rc->ray_dir_y * rc->ray_dir_y) / (rc->ray_dir_x * rc->ray_dir_x));
	rc->delta_dist_y = sqrt((double)1 +
	(rc->ray_dir_x * rc->ray_dir_x) / (rc->ray_dir_y * rc->ray_dir_y));
}

void		get_initial_dist(t_raycaster *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (double)((double)rc->p_pos_x - rc->map_x)
		* rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (double)((double)rc->map_x + (double)1 - rc->p_pos_x)
		* rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (double)((double)rc->p_pos_y - rc->map_y)
		* rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (double)((double)rc->map_y + (double)1 - rc->p_pos_y)
		* rc->delta_dist_y;
	}
}

void		dda(t_raycaster *rc, t_map *map)
{
	while (1)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (map->grid[rc->map_x][rc->map_y] == 1)
			break ;
	}
}

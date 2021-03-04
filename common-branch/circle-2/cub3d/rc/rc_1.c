/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:31:51 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 12:41:29 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

void		calcul_distance(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->wall_dist_perp = (double)((double)rc->map_x - rc->p_pos_x +
		(double)(1.0 - rc->step_x) / 2.0) / rc->ray_dir_x;
	else
		rc->wall_dist_perp = (double)((double)rc->map_y - rc->p_pos_y +
		(double)(1.0 - rc->step_y) / 2.0) / rc->ray_dir_y;
	rc->wall_height = (int)((double)rc->height / rc->wall_dist_perp);
	rc->wall_top = -rc->wall_height / 2 + rc->middle_height;
	if (rc->wall_top < 0)
		rc->wall_top = 0;
	rc->wall_bottom = rc->wall_height / 2 + rc->middle_height;
	if (rc->wall_bottom >= rc->height)
		rc->wall_bottom = rc->height - 1;
	if (rc->side == 0)
		rc->wall_x = rc->p_pos_y + rc->wall_dist_perp * rc->ray_dir_y;
	else
		rc->wall_x = rc->p_pos_x + rc->wall_dist_perp * rc->ray_dir_x;
	rc->texture_num = get_texture(rc);
	rc->wall_x -= floor(rc->wall_x);
	rc->texture_x = (int)(rc->wall_x * (double)rc->textures[rc->texture_num].w);
	if (rc->side == 0 && rc->ray_dir_x > 0)
		rc->texture_x = rc->textures[rc->texture_num].w - rc->texture_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		rc->texture_x = rc->textures[rc->texture_num].w - rc->texture_x - 1;
}

void		fire_ray(t_raycaster *rc, t_map *map)
{
	setup_ray(rc);
	get_initial_dist(rc);
	dda(rc, map);
	calcul_distance(rc);
}

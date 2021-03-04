/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:31:55 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/12 16:38:29 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

int			rgb_to_int(int r, int g, int b)
{
	int	c;

	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}

int			get_texture(t_raycaster *rc)
{
	if (rc->side == 0 && rc->ray_dir_x < 0)
		return (0);
	else if (rc->side == 0 && rc->ray_dir_x > 0)
		return (1);
	else if (rc->side == 1 && rc->ray_dir_y < 0)
		return (2);
	else
		return (3);
}

int			initialize_textures(t_raycaster *rc, t_map *map)
{
	rc->textures[0].ptr = mlx_xpm_file_to_image(rc->mlx_ptr,
	map->path_no, &rc->textures[0].w, &rc->textures[0].h);
	rc->textures[1].ptr = mlx_xpm_file_to_image(rc->mlx_ptr,
	map->path_so, &rc->textures[1].w, &rc->textures[1].h);
	rc->textures[2].ptr = mlx_xpm_file_to_image(rc->mlx_ptr,
	map->path_we, &rc->textures[2].w, &rc->textures[2].h);
	rc->textures[3].ptr = mlx_xpm_file_to_image(rc->mlx_ptr,
	map->path_ea, &rc->textures[3].w, &rc->textures[3].h);
	rc->textures[4].ptr = mlx_xpm_file_to_image(rc->mlx_ptr,
	map->path_sprite, &rc->textures[4].w, &rc->textures[4].h);
	return (1);
}

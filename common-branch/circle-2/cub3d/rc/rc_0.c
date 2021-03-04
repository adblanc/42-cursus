/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:27:55 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 16:59:18 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

int			handle_sprites(t_raycaster *rc, t_z_buffer *z_buffer)
{
	lst_sprites_distance(rc);
	sort_sprites(rc);
	project_sprites(rc, z_buffer);
	z_buffer_clear(&z_buffer);
	return (1);
}

int			cast_ray(t_raycaster *rc, t_map *map)
{
	t_z_buffer *z_buffer;

	z_buffer = NULL;
	rc->column = 0;
	if (rc->img_ptr)
		mlx_destroy_image(rc->mlx_ptr, rc->img_ptr);
	if (!(rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->width, rc->height)))
		return (display_error(ENOMEM, NULL));
	while (rc->column < rc->width)
	{
		fire_ray(rc, map);
		if (!(store_dist(&z_buffer, rc)) ||
		!(draw_on_image(rc->column, rc->wall_bottom, rc->wall_top, rc)))
			return (0);
		if (!(draw_floor_and_ceiling(rc->column++, rc)))
			return (0);
	}
	handle_sprites(rc, z_buffer);
	create_health_bar(rc);
	create_minimap(rc);
	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr, rc->img_ptr, 0, 0);
	mlx_string_put(rc->mlx_ptr, rc->win_ptr,
	rc->width / 10, rc->height * 0.9,
	rgb_to_int(0, 0, 0), "100%");
	return (1);
}

int			program_end(t_raycaster *rc)
{
	free_map(rc->map);
	sprites_clear(&rc->sprites);
	if (rc->img_ptr)
		mlx_destroy_image(rc->mlx_ptr, rc->img_ptr);
	if (rc->win_ptr)
		mlx_destroy_window(rc->mlx_ptr, rc->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int			handle_raycasting(t_map *map)
{
	t_raycaster rc;

	initialize_rc(&rc, map);
	if (!(rc.mlx_ptr = mlx_init()) ||
	!(rc.win_ptr =
	mlx_new_window(rc.mlx_ptr, rc.width, rc.height, "Cub3D")))
	{
		display_error(0, "Failed to initialize mlx connection.\n");
		return (program_end(&rc));
	}
	initialize_textures(&rc, map);
	if (!(find_sprites(&rc, map)))
		return (program_end(&rc));
	if (!(cast_ray(&rc, map)))
		return (program_end(&rc));
	if (rc.map->save)
	{
		create_bmp(&rc);
		program_end(&rc);
	}
	mlx_hook(rc.win_ptr, 2, 0, &handle_keys, &rc);
	mlx_hook(rc.win_ptr, 17, 0, &program_end, &rc);
	mlx_loop(rc.mlx_ptr);
	return (program_end(&rc));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:00:05 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 15:57:28 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rc/rc.h"

int			limit(int a, int limit)
{
	if (a > limit)
		a = limit;
	else if (a < 0)
		a = 0;
	return (a);
}

int			get_data_from_texture(t_raycaster *rc)
{
	t_data	d;
	int		i;

	i = 0;
	if (!(rc->textures[rc->texture_num].data =
	(int *)mlx_get_data_addr(rc->textures[rc->texture_num].ptr,
	&d.bpr, &d.size, &d.endian)))
		return (display_error(ENOMEM, NULL));
	return (1);
}

int			draw_floor_and_ceiling(int x, t_raycaster *rc)
{
	int		i;

	i = 1;
	while (rc->wall_bottom + i < rc->height)
	{
		rc->img_data[limit(x + (rc->wall_bottom + i) * rc->width,
		(rc->width) * (rc->height) - 1)] = rc->floor_color;
		i++;
	}
	i = 1;
	while (rc->wall_top - i >= 0)
	{
		rc->img_data[limit(x + (rc->wall_top - i) * rc->width,
		(rc->width) * (rc->height) - 1)] = rc->ceiling_color;
		i++;
	}
	return (1);
}

int			draw_on_image(int x, int y2, int y1, t_raycaster *rc)
{
	t_data	d;
	int		i;
	int		width;

	width = rc->textures[rc->texture_num].w;
	i = 0;
	if (!(get_data_from_texture(rc)))
		return (0);
	if (!(rc->img_data = (int *)
	mlx_get_data_addr(rc->img_ptr, &d.bpr, &d.size, &d.endian)))
		return (display_error(ENOMEM, NULL));
	while (i < y2 - y1)
	{
		d.d = (y1 + i) * 256 - rc->height * 128 + rc->wall_height * 128;
		d.tex_y = ((d.d * rc->textures[rc->texture_num].h)
		/ rc->wall_height) / 256;
		rc->img_data[limit(x + ((y1 + i) * rc->width),
		(rc->width) * (rc->height) - 1)] =
		rc->textures[rc->texture_num].data[limit(rc->texture_x +
		((d.tex_y) * width)
		, (width) * (rc->textures[rc->texture_num].h) - 1)];
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:50:36 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 14:37:26 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rc/rc.h"

void	vertical_loop(int j, t_raycaster *rc, t_data *d, t_sprite_proj *p)
{
	d->d = (j + p->start_y) * 256 - rc->height * 128 + p->sprite_height * 128;
	d->tex_y = ((d->d * rc->textures[4].h) / p->sprite_height) / 256;
	d->color = rc->textures[4].data[limit(d->tex_x +
	((d->tex_y) * rc->textures[4].w),
	(rc->textures[4].w) * (rc->textures[4].h) - 1)];
}

void	loop_through_sprite(t_raycaster *rc, t_sprite_proj *p,
t_z_buffer *buffer)
{
	t_data		d;
	t_z_buffer	*column;
	int			i;
	int			j;

	i = -1;
	j = -1;
	column = NULL;
	while (++i + p->start_x < p->end_x)
	{
		d.tex_x = (int)(256 * (i + p->start_x -
		(-p->sprite_width / 2 + p->sprite_screen_x))
		* rc->textures[4].w / p->sprite_width) / 256;
		column = find_column_wall_dist(buffer, i + p->start_x);
		j = 0;
		if (p->transform_y > 0 && i + p->start_x > 0
		&& i + p->start_x < rc->width && p->transform_y < column->dist)
			while (++j + p->start_y < p->end_y)
			{
				vertical_loop(j, rc, &d, p);
				if ((d.color & 0x00FFFFFF) != 0)
					rc->img_data[limit(i + p->start_x + ((j + p->start_y)
					* rc->width), (rc->width) * (rc->height) - 1)] = d.color;
			}
	}
}

int		draw_sprites(t_raycaster *rc, t_sprite_proj *proj, t_z_buffer *buffer)
{
	int			i;
	int			j;

	j = 0;
	i = 0;
	if (!(get_data_from_sprite_texture(rc)))
		return (0);
	loop_through_sprite(rc, proj, buffer);
	return (1);
}

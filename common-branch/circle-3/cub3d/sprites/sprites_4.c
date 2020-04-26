/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:30:09 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 13:41:21 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rc/rc.h"

void	transform_sprites(t_raycaster *rc, t_sprites *s, t_sprite_proj *proj)
{
	proj->sprite_x = s->pos_x - rc->p_pos_x;
	proj->sprite_y = s->pos_y - rc->p_pos_y;
	proj->inv_det = 1.0 / (rc->p_plane_x * rc->p_dir_y
	- rc->p_dir_x * rc->p_plane_y);
	proj->transform_x = proj->inv_det
	* (rc->p_dir_y * proj->sprite_x - rc->p_dir_x * proj->sprite_y);
	proj->transform_y = proj->inv_det
	* (-rc->p_plane_y * proj->sprite_x + rc->p_plane_x * proj->sprite_y);
	proj->sprite_screen_x = (int)((rc->width / 2)
	* (1 + proj->transform_x / proj->transform_y));
}

void	get_sprites_dimensions(t_raycaster *rc, t_sprite_proj *proj)
{
	proj->sprite_height = abs((int)(rc->height / (proj->transform_y)));
	proj->start_y = -proj->sprite_height / 2 + rc->middle_height;
	if (proj->start_y < 0)
		proj->start_y = 0;
	proj->end_y = proj->sprite_height / 2 + rc->middle_height;
	if (proj->end_y >= rc->height)
		proj->end_y = rc->height - 1;
	proj->sprite_width = abs((int)(rc->height / (proj->transform_y)));
	proj->start_x = -proj->sprite_width / 2 + proj->sprite_screen_x;
	if (proj->start_x < 0)
		proj->start_x = 0;
	proj->end_x = proj->sprite_width / 2 + proj->sprite_screen_x;
	if (proj->end_x >= rc->width)
		proj->end_x = rc->width - 1;
}

int		get_data_from_sprite_texture(t_raycaster *rc)
{
	int		bpr;
	int		size_line;
	int		endian;
	int		i;

	i = 0;
	endian = 1;
	size_line = rc->textures[4].w;
	bpr = 4;
	if (!(rc->textures[4].data = (int *)
	mlx_get_data_addr(rc->textures[4].ptr, &bpr, &size_line, &endian)))
		return (display_error(ENOMEM, NULL));
	return (1);
}

void	project_sprites(t_raycaster *rc, t_z_buffer *buffer)
{
	t_sprites		*current;
	t_sprite_proj	proj;

	current = rc->sprites;
	if (!rc->sprites)
		return ;
	while (current)
	{
		transform_sprites(rc, current, &proj);
		get_sprites_dimensions(rc, &proj);
		draw_sprites(rc, &proj, buffer);
		current = current->next;
	}
}

void	sprites_clear(t_sprites **lst)
{
	t_sprites *current;
	t_sprites *next;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

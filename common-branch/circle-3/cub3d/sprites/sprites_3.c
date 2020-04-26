/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:19:47 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/12 18:34:44 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rc/rc.h"

void			swap(t_sprites *a, t_sprites *b)
{
	int		temp_dist;
	double	temp_pos_x;
	double	temp_pos_y;
	int		temp_sprite_num;

	temp_dist = a->dist;
	temp_pos_x = a->pos_x;
	temp_pos_y = a->pos_y;
	temp_sprite_num = a->sprite_num;
	a->dist = b->dist;
	a->pos_x = b->pos_x;
	a->pos_y = b->pos_y;
	a->sprite_num = b->sprite_num;
	b->dist = temp_dist;
	b->pos_x = temp_pos_x;
	b->pos_y = temp_pos_y;
	b->sprite_num = temp_sprite_num;
}

void			sort_sprites(t_raycaster *rc)
{
	t_sprites	*ptr_1;
	t_sprites	*last_ptr;
	int			swapped;

	swapped = 1;
	ptr_1 = rc->sprites;
	last_ptr = NULL;
	if (!rc->sprites)
		return ;
	while (swapped)
	{
		swapped = 0;
		while (ptr_1->next)
		{
			if (ptr_1->dist < ptr_1->next->dist)
			{
				swap(ptr_1, ptr_1->next);
				swapped = 1;
			}
			ptr_1 = ptr_1->next;
		}
	}
}

t_z_buffer		*find_column_wall_dist(t_z_buffer *buffer, int column)
{
	t_z_buffer	*temp;

	temp = buffer;
	if (!buffer)
		return (NULL);
	while (temp)
	{
		if (temp->i == column)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

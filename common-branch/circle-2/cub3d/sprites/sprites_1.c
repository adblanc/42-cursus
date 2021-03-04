/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:20:28 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/13 13:00:35 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map/map.h"

void		lst_sprite_add_front(t_sprites **alst, t_sprites *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

t_sprites	*lst_sprite_new(double x, double y, int sprite_num)
{
	t_sprites *elem;

	if (!(elem = (t_sprites *)malloc(sizeof(t_sprites))))
		return (NULL);
	elem->pos_x = x;
	elem->pos_y = y;
	elem->sprite_num = sprite_num;
	elem->dist = 0;
	elem->next = NULL;
	return (elem);
}

void		lst_sprites_distance(t_raycaster *rc)
{
	t_sprites *temp;

	if (rc->sprites == NULL)
		return ;
	temp = rc->sprites;
	while (temp != NULL)
	{
		temp->dist = ((rc->p_pos_x - temp->pos_x) *
		(rc->p_pos_x - temp->pos_x) + (rc->p_pos_y - temp->pos_y)
		* (rc->p_pos_y - temp->pos_y));
		temp = temp->next;
	}
}

int			find_sprites(t_raycaster *rc, t_map *map)
{
	t_sprites	*sprite;
	int			i;
	int			j;

	sprite = NULL;
	i = 1;
	j = 1;
	while (i < map->line_nbr)
	{
		j = 1;
		while (j < map->column_nbr)
		{
			if (map->grid[i][j] > 1)
			{
				if (!(sprite = lst_sprite_new((double)i + 0.5,
				(double)j + 0.5, map->grid[i][j])))
					return (display_error(ENOMEM, NULL));
				lst_sprite_add_front(&rc->sprites, sprite);
			}
			j++;
		}
		i++;
	}
	return (1);
}

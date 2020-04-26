/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_player_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:07:24 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 17:31:58 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void		ft_set_p_dir(t_map *map, double x, double y)
{
	map->p.dir_x = x;
	map->p.dir_y = y;
}

static void		ft_set_p_plane(t_map *map, double x, double y)
{
	map->p.plane_x = x;
	map->p.plane_y = y;
}

int				ft_set_p_pos(t_map *map, int x, char orientation)
{
	if (map->p.pos_x != -1)
		return (display_error(0, "Multiple player positions.\n"));
	map->p.pos_x = map->line_nbr - 1;
	map->p.pos_y = x - 1;
	if (orientation == 'N')
	{
		ft_set_p_dir(map, -0.9999, 0.0001);
		ft_set_p_plane(map, -0.0001, 0.66);
	}
	else if (orientation == 'S')
	{
		ft_set_p_dir(map, 0.9999, 0.0001);
		ft_set_p_plane(map, -0.0001, -0.66);
	}
	else if (orientation == 'E')
	{
		ft_set_p_dir(map, 0.0001, -1.0001);
		ft_set_p_plane(map, -0.66, -0.0001);
	}
	else if (orientation == 'W')
	{
		ft_set_p_dir(map, 0, -1.0001);
		ft_set_p_plane(map, -0.66, 0);
	}
	return (1);
}

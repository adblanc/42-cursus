/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 09:03:56 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 18:06:09 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map/map.h"

void		ft_init_new_map_2(t_map *map)
{
	map->floor.r = 0;
	map->floor.g = 0;
	map->floor.b = 0;
	map->ceiling.r = 0;
	map->ceiling.g = 0;
	map->ceiling.b = 0;
	map->p.orientation = 0;
	map->p.pos_x = -1;
	map->p.pos_y = -1;
	map->p.dir_x = 0;
	map->p.dir_y = 0;
	map->p.plane_x = 0;
	map->p.plane_y = 0;
	map->p.mv_spd = 1;
	map->p.rt_spd = 1;
}

t_map		*ft_init_new_map(void)
{
	t_map *map;

	if (!(map = malloc(sizeof(t_map))))
		return (NULL);
	map->map_index = 0;
	map->line_nbr = 0;
	map->column_nbr = 0;
	map->info_count = 0;
	map->path_no = NULL;
	map->path_so = NULL;
	map->path_we = NULL;
	map->path_ea = NULL;
	map->path_sprite = NULL;
	map->grid = NULL;
	map->save = 0;
	ft_init_new_map_2(map);
	return (map);
}

int			free_map(t_map *map)
{
	int i;

	i = 0;
	free(map->path_no);
	free(map->path_so);
	free(map->path_we);
	free(map->path_ea);
	free(map->path_sprite);
	while (map->grid && i < map->line_nbr)
		free(map->grid[i++]);
	free(map->grid);
	free(map);
	return (1);
}

int			ft_end(t_map *map, int status)
{
	free_map(map);
	if (status == 0)
	{
		exit(EXIT_FAILURE);
		return (0);
	}
	exit(EXIT_SUCCESS);
	return (1);
}

int			main(int argc, char **argv)
{
	t_map *map;

	if (!(map = ft_init_new_map()))
		return (display_error(ENOMEM, NULL));
	if (!ft_check_args(argc, argv, map))
		return (ft_end(map, 0));
	if (!ft_check_file(argv[1], map))
		return (ft_end(map, 0));
	if (!ft_trim_map(argv[1], map))
		return (ft_end(map, 0));
	if (!(handle_raycasting(map)))
		return (ft_end(map, 0));
	return (ft_end(map, 1));
}

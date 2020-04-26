/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ids_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:47:25 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/13 17:48:04 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int		ft_check_n(char *line, t_map *map)
{
	if (!line || line[0] != 'O')
		return (display_error(0, "Bad character after N.\n"));
	line++;
	while (*line == ' ')
		line++;
	if (!(map->path_no = ft_strdup(line)))
		return (display_error(ENOMEM, NULL));
	if ((open(map->path_no, O_RDONLY) < 0))
		return (display_error(0, "NO path is invalid.\n"));
	map->info_count += 1;
	return (1);
}

int		ft_check_so(char *line, t_map *map)
{
	if (!line || line[0] != 'O')
		return (display_error(0, "Bad character after S.\n"));
	line++;
	while (*line == ' ')
		line++;
	if (!(map->path_so = ft_strdup(line)))
		return (display_error(ENOMEM, NULL));
	if ((open(map->path_so, O_RDONLY) < 0))
		return (display_error(0, "SO path is invalid.\n"));
	map->info_count += 1;
	return (1);
}

int		ft_check_w(char *line, t_map *map)
{
	if (!line || line[0] != 'E')
		return (display_error(0, "Bad character after W.\n"));
	line++;
	line = skip_spaces(line);
	if (!(map->path_we = ft_strdup(line)))
		return (display_error(ENOMEM, NULL));
	if ((open(map->path_we, O_RDONLY) < 0))
		return (display_error(0, "WE path is invalid.\n"));
	map->info_count += 1;
	return (1);
}

int		ft_check_e(char *line, t_map *map)
{
	if (!line || line[0] != 'A')
		return (display_error(0, "Bad character after E.\n"));
	line++;
	line = skip_spaces(line);
	if (!(map->path_ea = ft_strdup(line)))
		return (display_error(ENOMEM, NULL));
	if ((open(map->path_ea, O_RDONLY) < 0))
		return (display_error(0, "EA path is invalid.\n"));
	map->info_count += 1;
	return (1);
}

int		ft_check_both_s(char *line, t_map *map)
{
	if (!line || !line[0])
		return (display_error(0, "Bad character after S.\n"));
	if (line[0] != 'O')
		return (ft_check_sp(line, map));
	return (ft_check_so(line, map));
}

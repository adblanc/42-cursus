/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ids_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:47:19 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/13 17:44:35 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	*skip_spaces(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

int		ft_check_r(char *line, t_map *map)
{
	if (!line || !line[0])
		return (display_error(0, "Resolution parameter is not correct.\n"));
	line = skip_spaces(line);
	if (!ft_isdigit(*line))
		return (display_error(0, "Resolution parameter is not correct.\n"));
	map->res.x = ft_atoi(line);
	if (map->res.x <= 0)
		return (display_error(0, "Resolution width is <= 0.\n"));
	line = line + ft_atoi_length(line);
	line = skip_spaces(line);
	if (!ft_isdigit(*line))
		return (display_error(0, "Resolution parameter is not correct.\n"));
	map->res.y = ft_atoi(line);
	line = line + ft_atoi_length(line);
	if (*line != '\0')
		return (display_error(0, "Resolution parameter is not correct.\n"));
	if (map->res.y <= 0)
		return (display_error(0, "Resolution height is <= 0.\n"));
	if (map->res.y > MAX_HEIGHT || map->res.x > MAX_WIDTH)
	{
		map->res.y = MAX_HEIGHT;
		map->res.x = MAX_WIDTH;
	}
	map->info_count += 1;
	return (1);
}

int		ft_check_sp(char *line, t_map *map)
{
	if (!line || !line[0])
		return (display_error(0, "Bad character after S.\n"));
	line++;
	line = skip_spaces(line);
	if (!(map->path_sprite = ft_strdup(line)))
		return (display_error(ENOMEM, NULL));
	if ((open(map->path_sprite, O_RDONLY) < 0))
		return (display_error(0, "S path is invalid.\n"));
	map->info_count += 1;
	return (1);
}

int		ft_check_f(char *line, t_map *map)
{
	if (!line || !line[0])
		return (display_error(0, "Bad character after F.\n"));
	map->floor.r = ft_atoi(line);
	if (map->floor.r < 0 || map->floor.r > 255)
		return (display_error(0, "Floor R value is out of range.\n"));
	line = line + ft_atoi_length(line);
	if (*line != ',')
		return (display_error(0, "Comma missing in F.\n"));
	line++;
	map->floor.g = ft_atoi(line);
	if (map->floor.g < 0 || map->floor.g > 255)
		return (display_error(0, "Floor G value is out of range.\n"));
	line = line + ft_atoi_length(line);
	if (*line != ',')
		return (display_error(0, "Comma missing in F.\n"));
	line++;
	map->floor.b = ft_atoi(line);
	if (map->floor.b < 0 || map->floor.b > 255)
		return (display_error(0, "Floor B value is out of range.\n"));
	line = line + ft_atoi_length(line);
	if (*line != '\0')
		return (display_error(0, "Floor parameter is not correct.\n"));
	map->info_count += 1;
	return (1);
}

int		ft_check_c(char *line, t_map *map)
{
	if (!line || !line[0])
		return (display_error(0, "Bad character after C.\n"));
	map->ceiling.r = ft_atoi(line);
	if (map->ceiling.r < 0 || map->ceiling.r > 255)
		return (display_error(0, "Ceiling R value is out of range.\n"));
	line = line + ft_atoi_length(line);
	if (*line != ',')
		return (display_error(0, "Comma missing in C.\n"));
	line++;
	map->ceiling.g = ft_atoi(line);
	if (map->ceiling.g < 0 || map->ceiling.g > 255)
		return (display_error(0, "Ceiling G value is out of range.\n"));
	line = line + ft_atoi_length(line);
	if (*line != ',')
		return (display_error(0, "Comma missing in F.\n"));
	line++;
	map->ceiling.b = ft_atoi(line);
	if (map->ceiling.b < 0 || map->ceiling.b > 255)
		return (display_error(0, "Ceiling B value is out of range.\n"));
	line = line + ft_atoi_length(line);
	if (*line != '\0')
		return (display_error(0, "Floor parameter is not correct.\n"));
	map->info_count += 1;
	return (1);
}

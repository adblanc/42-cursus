/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:24:02 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 17:55:46 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int			ft_check_first_last_lines(char *line, t_map *map)
{
	static int	is_first = 1;
	int			i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (display_error(0, "Map is not surrounded by walls.\n"));
		if (is_first && line[i] == '1')
			map->column_nbr++;
		i++;
	}
	if (is_first)
		is_first = 0;
	else
		map->line_nbr = map->line_nbr + 1;
	if (i <= 0)
		return (display_error(0, "There should not have char after map.\n"));
	return (1);
}

int			ft_check_line_integrity(char *line, t_map *map, int i, int i_nosp)
{
	if ((!(line[i] == '0' || line[i] == '1' || line[i] == '2'
		|| line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'E' || line[i] == 'W' || line[i] == ' ')))
		return (display_error(0, "Unknown character in the map.\n"));
	if (!ft_isdigit(line[i]) && line[i] != ' ')
		return (ft_set_p_pos(map, i_nosp, line[i]));
	return (1);
}

static int	ft_check_other_lines(char *line, t_map *map)
{
	int i;
	int index_nosp;

	index_nosp = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			index_nosp++;
		if (i == 0 && line[i] != '1')
			return (display_error(0, "Map is not surrounded by walls.\n"));
		else if (line[i] != '1' && line[i + 1] == '\0')
			return (display_error(0, "Map is not surrounded by walls.\n"));
		else if (!ft_check_line_integrity(line, map, i, index_nosp))
			return (0);
		i++;
	}
	if (i <= 2)
		return (display_error(0, "Map is not surrounded by walls.\n"));
	return (1);
}

int			ft_check_map_core(char *line, t_map *map)
{
	static int started = 0;

	if (!line)
		return (0);
	if (!started && line[0] == '\0')
	{
		map->map_index++;
		return (1);
	}
	map->line_nbr = map->line_nbr + 1;
	if (started <= 1)
	{
		started = 2;
		return (ft_check_first_last_lines(line, map));
	}
	return (ft_check_other_lines(line, map));
}

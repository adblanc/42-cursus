/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 09:47:49 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 18:14:04 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		ft_initialize_ids(t_info ids[7], char charset[7])
{
	ids[0] = &ft_check_n;
	ids[1] = &ft_check_both_s;
	ids[2] = &ft_check_w;
	ids[3] = &ft_check_e;
	ids[4] = &ft_check_r;
	ids[5] = &ft_check_f;
	ids[6] = &ft_check_c;
	charset[0] = 'N';
	charset[1] = 'S';
	charset[2] = 'W';
	charset[3] = 'E';
	charset[4] = 'R';
	charset[5] = 'F';
	charset[6] = 'C';
}

int			ft_check_info_line(char *line, t_map *map, t_info ids[7], char *set)
{
	int		i;

	if (!line)
		return (0);
	map->map_index++;
	if (!line[0])
		return (1);
	i = ft_in_charset(line[0], set);
	if (i < 0)
		return (display_error(0, "Information missing.\n"));
	if (!(*(ids[i]))(line + 1, map))
	{
		return (0);
	}
	return (1);
}

int			clean_exit_reading_file(int fd, char **line, int status)
{
	close(fd);
	free(*line);
	free(line);
	return (status);
}

int			ft_check_file_end(int fd, char **line, t_map *map)
{
	if (!ft_check_first_last_lines(*line, map))
		return (clean_exit_reading_file(fd, line, 0));
	if (map->p.pos_x == -1)
	{
		display_error(0, "Player position is not set.\n");
		return (clean_exit_reading_file(fd, line, 0));
	}
	return (clean_exit_reading_file(fd, line, 1));
}

int			ft_check_file(const char *path, t_map *map)
{
	int		fd;
	char	**line;
	t_info	ids[7];
	char	set[7];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (display_error(EBADF, NULL));
	if ((!(line = (char **)malloc(sizeof(char *) * 1))))
		return (display_error(ENOMEM, NULL));
	ft_initialize_ids(ids, set);
	while (get_next_line(fd, line) > 0)
	{
		if (map->info_count < INFOS_NBR)
		{
			if (!ft_check_info_line(*line, map, ids, set))
				return (clean_exit_reading_file(fd, line, 0));
		}
		else if (!ft_check_map_core(*line, map))
			return (clean_exit_reading_file(fd, line, 0));
		free(*line);
	}
	return (ft_check_file_end(fd, line, map));
}

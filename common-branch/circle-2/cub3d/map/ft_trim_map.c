/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 09:22:55 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/13 19:15:28 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static size_t	ft_strlen_trimmed(const char *s)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != ' ')
			j++;
		i++;
	}
	return (j);
}

static int		*ft_str_trim_cpy(int *dst, const char *s)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] != ' ')
		{
			if (s[i] == 'N' || s[i] == 'E' || s[i] == 'S' || s[i] == 'W')
				dst[j] = 0;
			else
				dst[j] = s[i] - 48;
			j++;
		}
		i++;
	}
	return (dst);
}

static int		*ft_str_trim_dup(const char *s1)
{
	size_t	length;
	int		*ptr;

	length = ft_strlen_trimmed(s1);
	if (!(ptr = (int *)malloc(sizeof(int) * length)))
		return (NULL);
	ptr = ft_str_trim_cpy(ptr, s1);
	return (ptr);
}

static char		**ft_initialize_trim(int fd, t_map *map)
{
	int		i;
	char	**line;

	i = 0;
	if (!(map->grid = (int **)malloc(sizeof(int *) * (map->line_nbr)))
	|| !(line = (char **)malloc(sizeof(char *) * 1)))
		return (NULL);
	while (i < map->line_nbr)
		map->grid[i++] = NULL;
	i = 0;
	while (i < map->map_index && get_next_line(fd, line) > 0)
	{
		i++;
		free(*line);
	}
	return (line);
}

int				ft_trim_map(const char *path, t_map *map)
{
	int		j;
	int		fd;
	char	**line;

	j = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (display_error(EBADF, NULL));
	if (!(line = ft_initialize_trim(fd, map)))
		return (display_error(ENOMEM, NULL));
	while (get_next_line(fd, line) > 0)
	{
		if (!(map->grid[j] = ft_str_trim_dup(*line)))
			return (display_error(ENOMEM, NULL));
		free(*line);
		j++;
	}
	if (!(map->grid[j++] = ft_str_trim_dup(*line)))
		return (display_error(ENOMEM, NULL));
	free(*line);
	free(line);
	close(fd);
	return (1);
}

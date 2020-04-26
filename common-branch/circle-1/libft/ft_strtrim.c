/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:02:37 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/09 14:50:31 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_belongs_to(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	ft_find_start(char const *s1, char const *set)
{
	unsigned int i;

	i = 0;
	while (s1[i] && ft_belongs_to(s1[i], set) == 1)
		i++;
	return (i);
}

static size_t		ft_find_end(char const *s1, char const *set, size_t index)
{
	size_t res;

	res = index;
	while (res != 0 && ft_belongs_to(s1[res], set) == 1)
		res--;
	return (res);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			end;
	char			*res;

	if (ft_strlen(s1) != 0)
	{
		start = ft_find_start(s1, set);
		end = ft_find_end(s1, set, ft_strlen(s1) - 1);
	}
	if (ft_strlen(s1) == 0 || end < start)
	{
		res = (char *)malloc(sizeof(char));
		res[0] = '\0';
		return (res);
	}
	if (!(res = ft_substr(s1, start, end - start + 1)))
		return (NULL);
	return (res);
}

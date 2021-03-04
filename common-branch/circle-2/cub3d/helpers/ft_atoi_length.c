/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 12:54:09 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 16:43:06 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map/map.h"

int	ft_atoi_length(const char *str)
{
	int count;

	count = 0;
	if (!str)
		return (-1);
	while (*str && *str == ' ')
	{
		count++;
		str++;
	}
	if (*str && (*str == '-' || *str == '+'))
	{
		str++;
		count++;
	}
	while (*str && ft_isdigit(*str))
	{
		count++;
		str++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:29:35 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 16:43:46 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map/map.h"

int	ft_atoi(const char *str)
{
	int result;
	int sign;

	sign = 1;
	result = 0;
	if (!str)
		return (-1);
	while (*str && *str == ' ')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && (ft_isdigit(*str)))
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}

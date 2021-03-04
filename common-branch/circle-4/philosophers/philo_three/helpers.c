/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:11:55 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 17:21:39 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				ft_putnbr(int nb)
{
	char	c;

	if (nb / 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

void				ft_putstr(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

int					ft_atoi(const char *str)
{
	int result;
	int sign;

	sign = 1;
	result = 0;
	while (*str && (*str == '\r' || *str == '\n' || *str == '\t'
	|| *str == '\v' || *str == '\f' || *str == ' '))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (-1);
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}

void				ft_itoa(char *str, int nb)
{
	static int	i = 0;
	static int	beg = 1;
	int			first;

	first = beg ? 1 : 0;
	beg = 0;
	if (nb / 10)
		ft_itoa(str, nb / 10);
	str[i++] = nb % 10 + '0';
	if (first)
	{
		str[i] = '\0';
		i = 0;
		beg = 1;
	}
}

void				ft_append_str(char *s1, char *s2)
{
	while (*s1)
		s1++;
	while (*s2)
		*(s1++) = *(s2++);
	*s1 = *s2;
}

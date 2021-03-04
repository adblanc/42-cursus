/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:13:55 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 19:22:19 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			ft_putnbr(int nb)
{
	char	c;

	if (nb / 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

void			ft_putstr(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

int				str_error(char *s, int status)
{
	ft_putstr(2, s);
	ft_putstr(2, "\n");
	return (status);
}

void			ft_append_str(char *s1, char *s2)
{
	while (*s1)
		s1++;
	while (*s2)
		*(s1++) = *(s2++);
	*s1 = *s2;
}

int				ft_atoi(const char *str)
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

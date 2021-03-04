/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:58:47 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 19:20:33 by ablanc           ###   ########.fr       */
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

void			philo_display(t_philo *philo, int timestamp, char *msg)
{
	static int		last_timestamp = 0;

	pthread_mutex_lock(&(philo->info->print_ex));
	timestamp = last_timestamp > timestamp ? last_timestamp : timestamp;
	last_timestamp = timestamp;
	if (philo->info->state != RUNNING)
	{
		pthread_mutex_unlock(&(philo->info->print_ex));
		return ;
	}
	while (*msg)
	{
		ft_putnbr(timestamp);
		ft_putstr(1, " ");
		ft_putnbr(philo->id + 1);
		ft_putstr(1, " ");
		while (*msg && *msg != '|')
			write(1, msg++, 1);
		ft_putstr(1, "\n");
		if (*msg)
			++msg;
	}
	pthread_mutex_unlock(&(philo->info->print_ex));
}

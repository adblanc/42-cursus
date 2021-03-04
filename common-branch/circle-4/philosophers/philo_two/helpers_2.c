/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:15:05 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 19:15:51 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_display(t_philo *philo, int timestamp, char *msg)
{
	sem_wait(philo->info->print_sem);
	if (philo->info->state != RUNNING)
	{
		sem_post(philo->info->print_sem);
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
			msg++;
	}
	sem_post(philo->info->print_sem);
}

void	ft_itoa(char *str, int nb)
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

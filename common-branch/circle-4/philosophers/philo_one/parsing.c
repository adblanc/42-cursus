/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:20:28 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 17:20:33 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				ft_parsing(t_info *info, char **av, int ac)
{
	if ((info->number = ft_atoi(av[1])) <= 1)
		return (str_error("Philosopher number must be greater than 1.", 0));
	if ((info->time_die = ft_atoi(av[2])) <= 0)
		return (str_error("Time to die must be greater than 0.", 0));
	if ((info->time_eat = ft_atoi(av[3])) <= 0)
		return (str_error("Time to eat must be greater than 0.", 0));
	if ((info->time_sleep = ft_atoi(av[4])) <= 0)
		return (str_error("Time to sleep must be greater than 0.", 0));
	if (ac == 6)
	{
		if ((info->nbr_eat = ft_atoi(av[5])) <= 0)
			return (str_error("Nbr of time philos must eat must be > 0.", 0));
	}
	else
		info->nbr_eat = -1;
	info->state = RUNNING;
	return (1);
}

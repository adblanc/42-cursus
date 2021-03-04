/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:16:14 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 18:55:53 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		init_fork(t_fork *fork)
{
	fork->owner = -1;
	fork->used = 0;
	pthread_mutex_init(&fork->ex, NULL);
}

static void		init_philo(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->number)
	{
		info->lst_philo[i].id = i;
		info->lst_philo[i].nbr_eat = 0;
		info->lst_philo[i].eat_start = 0;
		pthread_mutex_init(&info->lst_philo[i].eat_ex, NULL);
		info->lst_philo[i].state = SLEEPING;
		init_fork(&info->lst_philo[i].fork);
		info->lst_philo[i].info = info;
		pthread_create(&info->lst_philo[i].thread, NULL, philo_loop,
			(void *)(info->lst_philo + i));
	}
}

static void		init_mutex(t_info *info)
{
	pthread_mutex_init(&info->print_ex, NULL);
	pthread_mutex_init(&info->start_ex, NULL);
	pthread_mutex_lock(&info->start_ex);
}

void			init_all(t_info *info)
{
	init_mutex(info);
	init_philo(info);
	pthread_mutex_unlock(&(info->start_ex));
}

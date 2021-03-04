/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:16:38 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 19:19:41 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		test_philo_death(t_info *info)
{
	int		i;
	int		runtime;

	i = -1;
	while (++i < info->number)
	{
		pthread_mutex_lock(&info->lst_philo[i].eat_ex);
		runtime = elapsed_time();
		if (runtime - info->lst_philo[i].eat_start > info->time_die
			+ MS_DEATH)
		{
			philo_display(&info->lst_philo[i], runtime, "died");
			info->state = FINISHED;
			pthread_mutex_unlock(&info->lst_philo[i].eat_ex);
			return (1);
		}
		pthread_mutex_unlock(&info->lst_philo[i].eat_ex);
	}
	return (0);
}

int		test_philo_ate_too_much(t_info *info)
{
	int			i;

	if (info->nbr_eat == -1)
		return (0);
	i = -1;
	while (++i < info->number)
	{
		pthread_mutex_lock(&info->lst_philo[i].eat_ex);
		if (info->lst_philo[i].nbr_eat < info->nbr_eat)
		{
			pthread_mutex_unlock(&info->lst_philo[i].eat_ex);
			return (0);
		}
		pthread_mutex_unlock(&info->lst_philo[i].eat_ex);
	}
	info->state = FINISHED;
	return (1);
}

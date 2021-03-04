/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:17:44 by ablanc            #+#    #+#             */
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
		sem_wait(info->lst_philo[i].eating_sem);
		runtime = elapsed_time();
		if (runtime - info->lst_philo[i].eat_start > info->time_die)
		{
			philo_display(&info->lst_philo[i], runtime, "died");
			info->state = FINISHED;
			sem_post(info->lst_philo[i].eating_sem);
			sem_n_post(info->forks, info->number);
			return (1);
		}
		sem_post(info->lst_philo[i].eating_sem);
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
		sem_wait(info->lst_philo[i].eating_sem);
		if (info->lst_philo[i].nbr_eat < info->nbr_eat)
		{
			sem_post(info->lst_philo[i].eating_sem);
			return (0);
		}
		sem_post(info->lst_philo[i].eating_sem);
	}
	info->state = FINISHED;
	sem_n_post(info->forks, info->number / 2);
	return (1);
}

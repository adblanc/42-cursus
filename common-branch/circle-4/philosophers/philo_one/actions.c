/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:07:46 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 14:24:17 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork(t_philo *philo, t_philo *next)
{
	int		ret;

	ret = 0;
	if (!next)
		return (ret);
	pthread_mutex_lock(&philo->fork.ex);
	pthread_mutex_lock(&next->fork.ex);
	if ((philo->fork.owner != philo->id && !philo->fork.used)
		&& (next->fork.owner != philo->id && !next->fork.used))
	{
		philo->fork.owner = philo->id;
		next->fork.owner = philo->id;
		philo->fork.used = 1;
		next->fork.used = 1;
		ret = 1;
	}
	pthread_mutex_unlock(&philo->fork.ex);
	pthread_mutex_unlock(&next->fork.ex);
	return (ret);
}

static void	drop_fork(t_philo *philo, t_philo *next)
{
	pthread_mutex_lock(&philo->fork.ex);
	pthread_mutex_lock(&next->fork.ex);
	philo->fork.used = 0;
	next->fork.used = 0;
	pthread_mutex_unlock(&philo->fork.ex);
	pthread_mutex_unlock(&next->fork.ex);
}

void		philo_sleep(t_philo *philo)
{
	philo_display(philo, elapsed_time(), "is sleeping");
	usleep(philo->info->time_sleep * 1000);
	philo->state = THINKING;
}

void		philo_think(t_philo *philo, t_philo *next)
{
	philo_display(philo, elapsed_time(), "is thinking");
	while (philo->info->state == RUNNING && !take_fork(philo, next))
		usleep(MS_THREAD);
	philo->state = EATING;
}

void		philo_eat(t_philo *philo, t_philo *next)
{
	pthread_mutex_lock(&philo->eat_ex);
	philo_display(philo, elapsed_time(),
		"has taken a fork|has taken a fork|is eating");
	philo->nbr_eat++;
	philo->eat_start = elapsed_time();
	pthread_mutex_unlock(&philo->eat_ex);
	usleep(philo->info->time_eat * 1000);
	drop_fork(philo, next);
	philo->state = SLEEPING;
}

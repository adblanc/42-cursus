/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:17:03 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 14:24:24 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		philo_sleep(t_philo *philo)
{
	philo_display(philo, elapsed_time(), "is sleeping");
	usleep(philo->info->time_sleep * 1000);
	philo->state = THINKING;
}

void		philo_think(t_philo *philo)
{
	philo_display(philo, elapsed_time(), "is thinking");
	sem_wait(philo->info->forks);
	philo->state = EATING;
}

void		philo_eat(t_philo *philo)
{
	sem_wait(philo->eating_sem);
	philo_display(philo, elapsed_time(),
		"has taken a fork|has taken a fork|is eating");
	philo->nbr_eat++;
	philo->eat_start = elapsed_time();
	sem_post(philo->eating_sem);
	usleep(philo->info->time_eat * 1000);
	sem_post(philo->info->forks);
	philo->state = SLEEPING;
}

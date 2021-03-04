/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:48:44 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 15:53:56 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		philo_sleep(t_args *args)
{
	philo_display(args, elapsed_time(), "is sleeping");
	usleep(args->info.time_sleep * 1000);
	args->philo.state = THINKING;
}

void		philo_think(t_args *args)
{
	philo_display(args, elapsed_time(), "is thinking");
	sem_wait(args->info.uni_sem[forks]);
	args->philo.state = EATING;
}

void		philo_eat(t_args *args)
{
	sem_wait(args->info.sem_eating[args->philo.id]);
	philo_display(args, elapsed_time(),
		"has taken a fork|has taken a fork|is eating");
	sem_post(args->info.sem_nbr_eat[args->philo.id]);
	args->philo.eat_start = elapsed_time();
	sem_post(args->info.sem_eating[args->philo.id]);
	usleep(args->info.time_eat * 1000);
	sem_post(args->info.uni_sem[forks]);
	args->philo.state = SLEEPING;
}

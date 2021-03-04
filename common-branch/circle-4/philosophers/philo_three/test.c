/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:11:38 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 16:11:40 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*wait_stop(void *args)
{
	t_args	*arg;

	arg = (t_args *)args;
	sem_wait(arg->info.uni_sem[end]);
	arg->philo.g_state = FINISHED;
	sem_n_post(arg->info.sem_nbr_eat[arg->philo.id],
		arg->info.nbr_eat);
	return (NULL);
}

void	*test_philo_death(void *args)
{
	int		runtime;
	t_args	*arg;

	arg = (t_args *)args;
	while (arg->philo.g_state == RUNNING)
	{
		sem_wait(arg->info.sem_eating[arg->philo.id]);
		runtime = elapsed_time();
		if (runtime - arg->philo.eat_start
			> arg->info.time_die)
		{
			philo_display(arg, runtime, "died");
			sem_n_post(arg->info.uni_sem[end],
				arg->info.number + 1);
			sem_post(arg->info.sem_eating[arg->philo.id]);
			return (NULL);
		}
		sem_post(arg->info.sem_eating[arg->philo.id]);
		usleep(MS_THREAD);
	}
	return (NULL);
}

void	*main_wait_end(void *args)
{
	int		i;
	t_args	*arg;

	arg = (t_args *)args;
	if (arg->info.nbr_eat < 0)
		return (NULL);
	i = -1;
	while (++i < arg->info.number)
	{
		sem_n_wait(arg->info.sem_nbr_eat[i],
			arg->info.nbr_eat);
	}
	sem_n_post(arg->info.uni_sem[end],
		arg->info.number + 1);
	return (NULL);
}

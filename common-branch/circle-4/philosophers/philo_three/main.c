/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:11:16 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 17:16:02 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_loop(t_args *args)
{
	pthread_create(&args->philo.stop_thread, NULL, wait_stop, (void *)args);
	pthread_create(&args->philo.death_thread, NULL,
	test_philo_death, (void *)args);
	while (args->philo.g_state == RUNNING)
	{
		if (args->philo.state == SLEEPING)
			philo_sleep(args);
		else if (args->philo.state == THINKING)
			philo_think(args);
		else if (args->philo.state == EATING)
			philo_eat(args);
	}
	pthread_join(args->philo.stop_thread, NULL);
	pthread_join(args->philo.death_thread, NULL);
}

int		main(int ac, char **av)
{
	t_args		args;
	pthread_t	end_thread;
	int			ret;

	clean_sem(&args.info, NO_CLOSE_SEM);
	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(&args.info, av, ac) == 0)
			return (0);
		init_all(&args);
		pthread_create(&end_thread, NULL, main_wait_end, (void *)&args);
		pthread_join(end_thread, NULL);
		sem_wait(args.info.uni_sem[end]);
		clean_sem(&args.info, CLOSE_SEM);
	}
	return (0);
}

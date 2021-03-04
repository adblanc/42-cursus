/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:17:25 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 19:22:06 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->info->state == RUNNING)
	{
		if (philo->state == SLEEPING)
			philo_sleep(philo);
		else if (philo->state == THINKING)
			philo_think(philo);
		else if (philo->state == EATING)
			philo_eat(philo);
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_info		info;
	int			i;

	i = -1;
	clean_sem(&info, NO_CLOSE_SEM);
	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(&info, av, ac) == 0)
			return (0);
		init_all(&info);
		while (!test_philo_death(&info) && !test_philo_ate_too_much(&info))
			usleep(MS_MAIN);
		while (++i < info.number)
			pthread_join(info.lst_philo[i].thread, NULL);
	}
	clean_sem(&info, CLOSE_SEM);
	return (0);
}

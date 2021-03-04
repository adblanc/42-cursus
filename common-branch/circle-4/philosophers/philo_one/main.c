/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:16:07 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 19:19:41 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *arg)
{
	t_philo		*philo;
	t_philo		*next_philo;

	philo = (t_philo *)arg;
	next_philo = philo->info->lst_philo + (philo->id + 1) % philo->info->number;
	while (philo->info->state == RUNNING)
	{
		if (philo->state == SLEEPING)
			philo_sleep(philo);
		else if (philo->state == THINKING)
			philo_think(philo, next_philo);
		else if (philo->state == EATING)
			philo_eat(philo, next_philo);
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_info		info;
	int			i;

	i = -1;
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
	return (0);
}

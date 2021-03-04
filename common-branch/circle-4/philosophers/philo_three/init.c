/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:11:08 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 17:16:19 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		init_info(t_info *info)
{
	int		i;
	char	name[SEM_NAME_SIZE];

	info->uni_sem[print] = sem_open(SEM_DISPLAY, O_CREAT, 0666, 1);
	info->uni_sem[forks] = sem_open(SEM_FORKS, O_CREAT, 0666, info->number / 2);
	info->uni_sem[death] = sem_open(SEM_DEATH, O_CREAT, 0666, 0);
	info->uni_sem[end] = sem_open(SEM_END, O_CREAT, 0666, 0);
	i = -1;
	while (++i < info->number)
	{
		fill_sem_name(name, i, SEM_EATING);
		info->sem_eating[i] = sem_open(name, O_CREAT, 0666, 1);
		fill_sem_name(name, i, SEM_EAT_NBR);
		info->sem_nbr_eat[i] = sem_open(name, O_CREAT, 0666, 0);
	}
	return (0);
}

static void		init_philo(t_args *args)
{
	int		i;

	args->philo.eat_start = 0;
	args->philo.state = SLEEPING;
	args->philo.g_state = RUNNING;
	i = -1;
	while (++i < args->info.number)
	{
		args->philo.id = i;
		if (fork() == 0)
		{
			philo_loop(args);
			clean_sem(&args->info, CLOSE_SEM);
			exit(0);
		}
	}
}

void			init_all(t_args *args)
{
	init_info(&args->info);
	init_philo(args);
}

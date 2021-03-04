/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:17:19 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 15:10:44 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			init_philo(t_info *info)
{
	int		i;
	char	name[SEM_NAME_SIZE];

	i = -1;
	while (++i < info->number)
	{
		fill_eating_sem_name(i, name);
		info->lst_philo[i].id = i;
		info->lst_philo[i].nbr_eat = 0;
		info->lst_philo[i].eat_start = 0;
		info->lst_philo[i].eating_sem = sem_open(name, O_CREAT, 0666, 1);
		info->lst_philo[i].state = SLEEPING;
		info->lst_philo[i].info = info;
		pthread_create(&info->lst_philo[i].thread, NULL, philo_loop,
			(void *)(info->lst_philo + i));
	}
}

static void			init_sem(t_info *info)
{
	info->print_sem = sem_open(SEM_DISPLAY, O_CREAT, 0666, 1);
	info->forks = sem_open(SEM_FORKS, O_CREAT, 0666, info->number / 2);
}

void				init_all(t_info *info)
{
	init_sem(info);
	init_philo(info);
}

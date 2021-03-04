/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:17:37 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 16:07:32 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_eating_sem_name(int id, char *name)
{
	ft_itoa(name, id + 1);
	ft_append_str(name, "_eat_sem");
}

void	sem_n_post(sem_t *sem, int n)
{
	int		i;

	i = -1;
	while (++i < n)
		sem_post(sem);
}

void	clean_sem(t_info *info, t_close_sem close)
{
	int		i;
	char	name[SEM_NAME_SIZE];

	if (close == CLOSE_SEM)
	{
		sem_close(info->print_sem);
		sem_close(info->forks);
		i = -1;
		while (++i < info->number)
			sem_close(info->lst_philo[i].eating_sem);
	}
	sem_unlink(SEM_DISPLAY);
	sem_unlink(SEM_FORKS);
	i = -1;
	while (++i < PHILO_MAX)
	{
		fill_eating_sem_name(i, name);
		sem_unlink(name);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:11:32 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 17:21:00 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			fill_sem_name(char *name, int id, char *title)
{
	ft_itoa(name, id + 1);
	ft_append_str(name, title);
}

void			sem_n_post(sem_t *sem, int nb)
{
	int		i;

	i = -1;
	while (++i < nb)
		sem_post(sem);
}

void			sem_n_wait(sem_t *sem, int nb)
{
	int		i;

	i = -1;
	while (++i < nb)
		sem_wait(sem);
}

static void		close_sems(t_info *info)
{
	int	i;

	i = -1;
	sem_close(info->uni_sem[print]);
	sem_close(info->uni_sem[forks]);
	sem_close(info->uni_sem[death]);
	sem_close(info->uni_sem[end]);
	while (++i < info->number)
	{
		sem_close(info->sem_eating[i]);
		sem_close(info->sem_nbr_eat[i]);
	}
}

void			clean_sem(t_info *info, t_close_sem close)
{
	int		i;
	char	name[SEM_NAME_SIZE];

	i = -1;
	if (close == CLOSE_SEM)
		close_sems(info);
	sem_unlink(SEM_DISPLAY);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_END);
	while (++i < PHILO_MAX)
	{
		fill_sem_name(name, i, SEM_EATING);
		sem_unlink(name);
		fill_sem_name(name, i, SEM_EAT_NBR);
		sem_unlink(name);
	}
}

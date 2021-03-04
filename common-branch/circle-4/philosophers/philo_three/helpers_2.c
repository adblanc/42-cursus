/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:46:19 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 17:16:26 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			philo_display(t_args *args, int timestamp, char *msg)
{
	sem_wait(args->info.uni_sem[print]);
	if (args->philo.state == FINISHED)
	{
		sem_post(args->info.uni_sem[print]);
		return ;
	}
	while (*msg)
	{
		ft_putnbr(timestamp);
		ft_putstr(1, " ");
		ft_putnbr(args->philo.id + 1);
		ft_putstr(1, " ");
		while (*msg && *msg != '|')
			write(1, msg++, 1);
		ft_putstr(1, "\n");
		if (*msg)
			msg++;
	}
	sem_post(args->info.uni_sem[print]);
}

int				str_error(char *s, int status)
{
	ft_putstr(2, s);
	ft_putstr(2, "\n");
	return (status);
}

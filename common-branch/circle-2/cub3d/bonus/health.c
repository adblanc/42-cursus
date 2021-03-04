/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:17:13 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/14 16:58:16 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rc/rc.h"

int		create_health_bar(t_raycaster *rc)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < rc->width / 8)
	{
		j = 0;
		while (j < rc->height / 20)
		{
			rc->img_data[i + rc->width / 10 +
			((j + rc->height * 9 / 10) * rc->width)] = rgb_to_int(255, 0, 0);
			j++;
		}
		i++;
	}
	return (1);
}

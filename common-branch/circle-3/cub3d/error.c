/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:14:21 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/13 13:13:58 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/map.h"

int		display_error(int errnum, char *error)
{
	ft_putstr_fd("Error\n", 2);
	if (!error)
	{
		errno = errnum;
		ft_putstr_fd(strerror(errno), 2);
	}
	else
		ft_putstr_fd(error, 2);
	return (0);
}

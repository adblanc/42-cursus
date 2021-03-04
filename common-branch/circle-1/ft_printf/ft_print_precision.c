/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:42:31 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:34:40 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_precision(t_list *status)
{
	int i;

	i = 0;
	while (i < status->precision)
	{
		ft_putchar('0', status);
		i++;
	}
}

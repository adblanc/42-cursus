/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:07:53 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:10:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_padding(t_list *status, int side)
{
	int		i;
	char	c;

	c = status->zero && !status->minus ? '0' : ' ';
	i = -1;
	if (side == LEFT)
		while ((++i < status->padding) && !status->minus)
			ft_putchar(c, status);
	else if (side == RIGHT)
		while ((++i < status->padding) && status->minus)
			ft_putchar(c, status);
}

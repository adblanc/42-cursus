/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:51:15 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/23 19:15:45 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_status_init(t_list *status)
{
	status->res = NULL;
	status->count = 0;
	status->flags_to_skip = 1;
	status->is_neg = 0;
	status->minus = 0;
	status->padding = 0;
	status->zero = 0;
	status->precision = -1;
	status->is_num = 0;
	status->end = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:46:31 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:23:55 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex(t_list *s)
{
	if (s->padding <= 0 && s->precision == 0 && s->res[0] == '0')
		return ;
	ft_correct_flags(s);
	ft_correct_precision_zero(s);
	ft_print_padding(s, LEFT);
	ft_print_precision(s);
	ft_putstr(s->res, s);
	ft_print_padding(s, RIGHT);
}

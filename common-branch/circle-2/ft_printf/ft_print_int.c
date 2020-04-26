/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:44:30 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:24:01 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_int(t_list *s)
{
	if (s->padding <= 0 && s->precision == 0 && s->res[0] == '0')
		return ;
	ft_correct_flags(s);
	ft_correct_precision_zero(s);
	if (s->is_neg)
		s->padding--;
	if (s->is_neg && (!s->minus && s->precision <= 0 && s->zero))
		ft_putchar('-', s);
	ft_print_padding(s, LEFT);
	if (s->is_neg && (s->precision > 0))
		ft_putchar('-', s);
	ft_print_precision(s);
	if (s->is_neg && ((s->minus && s->precision <= 0)
	|| (!s->zero && s->precision <= 0)))
		ft_putchar('-', s);
	ft_putstr(s->res, s);
	ft_print_padding(s, RIGHT);
}

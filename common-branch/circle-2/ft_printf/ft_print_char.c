/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:25:16 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:23:08 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_char(t_list *s)
{
	s->precision = 0;
	ft_correct_flags(s);
	ft_print_padding(s, LEFT);
	ft_print_precision(s);
	if (s->res && s->res[0] == 0 && s->precision <= 0)
		ft_putchar('\0', s);
	else
		ft_putstr(s->res, s);
	ft_print_padding(s, RIGHT);
}

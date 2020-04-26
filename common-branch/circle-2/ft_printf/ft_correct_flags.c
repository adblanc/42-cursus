/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:47:33 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:32:41 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_correct_2(t_list *s, int len)
{
	if (s->precision >= 0 && s->res && s->is_num)
		s->zero = 0;
	if (s->padding < 0)
	{
		s->padding *= -1;
		s->zero = 0;
		s->minus = 1;
	}
	if (s->res == NULL)
	{
		if (s->precision > 0)
			s->precision = -1;
		s->padding = s->padding - len;
		return (0);
	}
	return (1);
}

void			ft_correct_flags(t_list *s)
{
	int	len;

	len = (int)ft_strlen(s->res);
	if (!len)
		len = 1;
	if (!(ft_correct_2(s, len)))
		return ;
	if (s->precision > len)
	{
		s->padding = s->padding - s->precision;
		s->precision = s->precision - len;
		if (s->is_num)
			s->zero = 0;
	}
	else
	{
		s->padding = s->padding - len;
		if (s->precision > 0)
			s->precision = -1;
	}
}

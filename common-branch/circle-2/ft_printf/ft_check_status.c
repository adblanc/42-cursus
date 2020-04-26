/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:55:27 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:10:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_check_2(char c, t_list *s, va_list ap)
{
	if (c == 's')
		if (!(s->res = ft_conv_string((const char *)va_arg(ap, char *), s)))
			return (0);
		else
			ft_print_string(s);
	else if (c == 'p')
		if (!(s->res = ft_conv_addr(va_arg(ap, void *), s)))
			return (0);
		else
			ft_print_addr(s);
	else if (c == 'c')
	{
		if (!(s->res = ft_conv_char(va_arg(ap, int))))
			return (0);
		else
			ft_print_char(s);
	}
	else
	{
		ft_print_char_special(c, s);
	}
	return (1);
}

int		ft_check_1(char c, t_list *s, va_list ap)
{
	if (c == 'd' || c == 'i')
		if (!(s->res = ft_conv_int(va_arg(ap, int), s)))
			return (0);
		else
			ft_print_int(s);
	else if (c == 'u')
		if (!(s->res = ft_conv_unsigned_int(va_arg(ap, unsigned int), s)))
			return (0);
		else
			ft_print_unsigned_int(s);
	else if (c == 'x')
		if (!(s->res = ft_conv_base(va_arg(ap, int), "0123456789abcdef", s)))
			return (0);
		else
			ft_print_hex(s);
	else if (c == 'X')
	{
		if (!(s->res = ft_conv_base(va_arg(ap, int), "0123456789ABCDEF", s)))
			return (0);
		ft_print_hex(s);
	}
	else
		return (ft_check_2(c, s, ap));
	return (1);
}

int		ft_check_if_legal(const char *s, int index)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	if (i != index - 1)
		return (0);
	return (1);
}

int		ft_check_status(const char *s, t_list *status, va_list ap)
{
	if (*s && *s == '0')
		status->zero = 1;
	ft_parse_flags(s + status->zero, status, ap);
	status->flags_to_skip = ft_check_flags_length(s);
	if (!(*(s + status->flags_to_skip)))
	{
		status->end = 1;
		return (1);
	}
	s = s + status->flags_to_skip;
	return (ft_check_1(*s, status, ap));
}

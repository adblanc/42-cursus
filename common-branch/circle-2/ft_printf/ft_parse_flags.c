/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:24:39 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/23 19:10:40 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_parse_precision(const char *s, t_list *stat, va_list ap)
{
	int erase;

	erase = 1;
	stat->precision = 0;
	while (*s && (ft_isdigit(*s) || *s == '-' || *s == '*' || *s == '.'))
	{
		if (*s == '*')
		{
			if (erase)
				stat->precision = va_arg(ap, int);
			return (ft_parse_flags(s + erase, stat, ap));
		}
		else if (*s == '-')
			return (ft_parse_flags(s, stat, ap));
		else if (*s == '.')
			return (ft_parse_precision(s + 1, stat, ap));
		else
		{
			stat->precision = erase ? *s - 48 : stat->precision * 10 + *s - 48;
			erase = 0;
		}
		s++;
	}
	return (1);
}

int		ft_parse_flags(const char *s, t_list *status, va_list ap)
{
	int erase;

	erase = 1;
	while (*s && (ft_isdigit(*s) || *s == '-' || *s == '*' || *s == '.'))
	{
		if (*s == '.')
			return (ft_parse_precision(s + 1, status, ap));
		else if (*s == '*')
			status->padding = va_arg(ap, int);
		else if (*s == '-')
		{
			status->minus = 1;
			erase = 1;
		}
		else if (*s == '0' && *(s - 1) && !ft_isdigit(*(s - 1)))
			status->zero = 1;
		else
		{
			status->padding = erase ? *s - 48 : status->padding * 10 + *s - 48;
			erase = 0;
		}
		s++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:10:21 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:24:49 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Avant de return la sum de toutes les length de la liste, free lst avec clear
*/

int				ft_handle_special(const char *str, t_list *status, va_list ap)
{
	ft_status_init(status);
	if (*str)
	{
		if (!(ft_check_status(str, status, ap)))
			return (0);
		free(status->res);
	}
	return (1);
}

static int		ft_parse(const char *str, int *count, t_list *stat, va_list ap)
{
	while (*str)
		if (*str == '%')
		{
			if (!(ft_handle_special(str++ + 1, stat, ap)))
				return (0);
			*count += stat->count;
			if (stat->end)
				break ;
			if (*str)
				str = str + stat->flags_to_skip + 1;
		}
		else
		{
			ft_putchar(*str, NULL);
			*count = *count + 1;
			str++;
		}
	return (1);
}

int				ft_printf(const char *str, ...)
{
	va_list		ap;
	t_list		*status;
	int			count;

	count = 0;
	if (!(status = (t_list *)malloc(sizeof(t_list))))
		return (-1);
	va_start(ap, str);
	if (!(ft_parse(str, &count, status, ap)))
		return (-1);
	free(status);
	va_end(ap);
	return (count);
}

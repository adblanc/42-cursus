/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags_length.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:07:47 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:10:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_check_flags_length(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (*s && (ft_isdigit(*s) || *s == '-' || *s == '*' || *s == '.'))
	{
		count++;
		s++;
	}
	return (count);
}

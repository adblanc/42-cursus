/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_addr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:47:44 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:10:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_count_char(unsigned long n)
{
	int count;

	count = 1;
	while (n > 15)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static char		*ft_convert_int(char *s, unsigned long n, int end_i, char *base)
{
	s[end_i--] = '\0';
	while (n > 15)
	{
		s[end_i--] = base[n % 16];
		n /= 16;
	}
	s[end_i--] = base[n % 16];
	return (s);
}

char			*ft_conv_addr(void *ptr, t_list *status)
{
	char			*res;
	int				count_char;
	unsigned long	n;

	n = (unsigned long)ptr;
	count_char = ft_count_char(n);
	if (!(res = (char *)malloc(sizeof(char) * (count_char + 1))))
		return (NULL);
	res = ft_convert_int(res, n, count_char, "0123456789abcdef");
	status->is_num = 1;
	return (res);
}

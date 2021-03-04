/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:09:52 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/09 14:50:31 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_char(long n)
{
	int count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	count++;
	return (count);
}

static char	*ft_convert_int(char *s, long n, int end_i)
{
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	s[end_i--] = '\0';
	while (n > 9)
	{
		s[end_i] = n % 10 + '0';
		end_i--;
		n /= 10;
	}
	s[end_i] = n % 10 + '0';
	return (s);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		count_char;

	count_char = ft_count_char((long)n);
	res = (char *)malloc(sizeof(char) * (count_char + 1));
	if (res == NULL)
		return (NULL);
	res = ft_convert_int(res, (long)n, count_char);
	return (res);
}

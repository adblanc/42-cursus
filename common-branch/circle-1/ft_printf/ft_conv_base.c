/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:43:22 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:10:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	check_base(char *base)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+' || base[i] == '.')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
			if (base[i] == base[j])
				return (0);
			else
				j++;
		i++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

static int		ft_count_char(unsigned int n, unsigned int len)
{
	int count;

	count = 0;
	while (n > len - 1)
	{
		count++;
		n /= len;
	}
	count++;
	return (count);
}

static char		*ft_convert_int(char *s, unsigned int n, int end_i, char *base)
{
	unsigned int	len;

	len = check_base(base);
	s[end_i--] = '\0';
	while (n > len - 1)
	{
		s[end_i] = base[n % len];
		end_i--;
		n /= len;
	}
	s[end_i] = base[n % len];
	return (s);
}

char			*ft_conv_base(unsigned int n, char *base, t_list *status)
{
	char			*res;
	int				count_char;
	unsigned int	base_length;

	if (base == NULL)
		return (NULL);
	base_length = check_base(base);
	if (!base_length)
		return (NULL);
	count_char = ft_count_char(n, base_length);
	res = (char *)malloc(sizeof(char) * (count_char + 1));
	if (res == NULL)
		return (NULL);
	res = ft_convert_int(res, n, count_char, base);
	status->is_num = 1;
	return (res);
}

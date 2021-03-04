/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:45:02 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:18:42 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_check_precision_length(t_list *status, int *length)
{
	if ((*length > status->precision && status->precision >= 0)
	|| status->precision == 0)
		*length = status->precision;
}

static char	*ft_str_null(t_list *status)
{
	char	*res;
	int		length;

	length = NULL_SIZE;
	if (!(res = malloc(sizeof(char) * length + 1)))
		return (NULL);
	res[0] = '(';
	res[1] = 'n';
	res[2] = 'u';
	res[3] = 'l';
	res[4] = 'l';
	res[5] = ')';
	res[6] = '\0';
	ft_check_precision_length(status, &length);
	if (length < NULL_SIZE)
		res[length] = '\0';
	return (res);
}

static char	*ft_strncpy(char *dst, const char *src, int n)
{
	int i;

	i = 0;
	if (src)
	{
		while (src[i] && i < n)
		{
			dst[i] = src[i];
			i++;
		}
	}
	while (i < n)
		dst[i++] = '\0';
	dst[i] = '\0';
	return (dst);
}

char		*ft_conv_string(const char *s1, t_list *status)
{
	int		length;
	char	*ptr;

	if (s1 == NULL && status->precision != 0)
		return (ft_str_null(status));
	length = (int)ft_strlen(s1);
	ft_check_precision_length(status, &length);
	if (!(ptr = (char *)malloc(sizeof(char) * length + 1)))
		return (NULL);
	ptr = ft_strncpy(ptr, s1, length);
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:32:13 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/12 10:56:47 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *source;

	source = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*source == (unsigned char)c)
			return (source);
		source++;
	}
	return (NULL);
}

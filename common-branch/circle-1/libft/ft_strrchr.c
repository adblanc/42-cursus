/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:41:50 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/12 10:59:58 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *temp;

	temp = NULL;
	while (*s)
	{
		if (*s == c)
			temp = (char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (temp);
}

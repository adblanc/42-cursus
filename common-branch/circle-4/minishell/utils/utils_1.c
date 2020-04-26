/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:17:03 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/04 20:16:24 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	put_char(int fd, char c)
{
	write(fd, &c, 1);
}

void	put_str(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

int		str_cmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*str_cpy(char *dst, const char *src)
{
	char	*save;

	save = dst;
	if (!src || !dst)
		return (dst);
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (save);
}

int		char_in_set(char c, char *charset)
{
	int i;

	i = -1;
	if (!charset)
		return (i);
	while (charset[++i])
		if (charset[i] == c)
			return (i);
	return (-1);
}

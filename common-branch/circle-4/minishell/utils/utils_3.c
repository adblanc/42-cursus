/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 22:22:54 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/04 20:16:33 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int		ft_atoi(const char *str)
{
	int result;
	int sign;

	sign = 1;
	result = 0;
	while (*str && (*str == '\r' || *str == '\n' || *str == '\t'
	|| *str == '\v' || *str == '\f' || *str == ' '))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n && ((s1[i] && s2[i] == '\0') || (s2[i] && s1[i] == '\0')))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t length;

	length = str_len(needle);
	i = 0;
	if (!length)
		return ((char *)haystack);
	while (haystack && haystack[i])
	{
		if (haystack[i] == *needle &&
		ft_strncmp(&haystack[i], needle, length) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (*s == c ? (char *)s : NULL);
}

size_t	strl_cpy(char *dst, const char *src, size_t size)
{
	size_t		i;

	if (!size)
		return (str_len(src));
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (str_len(src));
}

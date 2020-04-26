/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:25:06 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/25 16:39:32 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

static void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*pt_src;
	char	*pt_dst;

	if (dst == NULL && src == NULL)
		return (NULL);
	pt_src = (char *)src;
	pt_dst = (char *)dst;
	while (n--)
		*pt_dst++ = *pt_src++;
	return (dst);
}

char			*ft_malloc_null(void)
{
	char *str;

	str = (char *)malloc(sizeof(char));
	str[0] = '\0';
	return (str);
}

char			*ft_str_add_char(char *s1, char c)
{
	char	*res;
	size_t	length;

	if (s1 == NULL)
		return (NULL);
	length = ft_strlen(s1);
	if (!(res = (char *)malloc(sizeof(char) * (length + 1) + 1)))
		return (NULL);
	res = ft_memcpy(res, s1, length);
	res[length] = c;
	res[length + 1] = '\0';
	free(s1);
	return (res);
}

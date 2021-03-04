/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:08:52 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/07 18:24:50 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;
	int		in;

	in = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !in)
		{
			in = 1;
			count++;
		}
		if (*s == c && in)
			in = 0;
		s++;
	}
	return (count);
}

static size_t	ft_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int		ft_get_word(t_shell *sh, char **str, const char *src, char c)
{
	char	*letter;

	if (!(*str = ft_malloc(sh, scp_cmd, (ft_word_len(src, c) + 1)
		* sizeof(char))))
		return (1);
	letter = *str;
	while (*src && *src != c)
	{
		*letter = *src;
		letter++;
		src++;
	}
	*letter = '\0';
	return (0);
}

static char		**free_array(t_shell *sh, char ***array)
{
	while (**array)
	{
		ft_free(sh, **array);
		(*array)++;
	}
	ft_free(sh, *array);
	return (NULL);
}

char			**ft_split(t_shell *sh, char const *s, char c)
{
	char	**array;
	char	**array_sav;
	int		in;

	if (!s || !(array = ft_malloc(sh, scp_cmd, (ft_word_count(s, c) + 1)
		* sizeof(char *))))
		return (NULL);
	array_sav = array;
	in = 0;
	while (*s)
	{
		if (*s != c && !in)
		{
			in = 1;
			if (ft_get_word(sh, array, s, c))
				return (free_array(sh, &array_sav));
			array++;
		}
		in = *s == c && in ? 0 : in;
		s++;
	}
	*array = NULL;
	return (array_sav);
}

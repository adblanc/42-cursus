/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 14:20:51 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/12 19:54:01 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

size_t	str_len(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	display_error(int errnum, char *name, char *error)
{
	put_str(2, name);
	put_str(2, ": ");
	if (error && errnum == 0)
	{
		put_str(2, error);
		put_char(2, '\n');
	}
	else
	{
		errno = errnum;
		put_str(2, strerror(errno));
		if (error)
		{
			put_str(2, ": ");
			put_str(2, error);
		}
		put_char(2, '\n');
	}
}

void	display_error_with_arg(int errnum, char *name, char *arg, char *err)
{
	put_str(2, name);
	put_str(2, ": ");
	put_str(2, arg);
	put_str(2, ": ");
	if (err)
		put_str(2, err);
	else
	{
		errno = errnum;
		put_str(2, strerror(errno));
	}
	put_char(2, '\n');
}

size_t	str_len_2d(char **tab)
{
	size_t i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

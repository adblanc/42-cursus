/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:15:57 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/04 20:15:19 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static int		ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int		ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

static int		is_variable_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

size_t			variable_name_size(char *variable)
{
	size_t i;

	i = 0;
	if (!variable)
		return (i);
	while (is_variable_char(variable[i]))
		i++;
	return (i);
}

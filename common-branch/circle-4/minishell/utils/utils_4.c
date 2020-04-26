/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:59 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/04 20:16:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	parse_back_equals(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == '=' && (*(str + 1) == STR || *(str + 1) == CMD))
			str_cpy(str + 1, str + 2);
		str++;
	}
}

char	**check_all_args_for_equals(char **args)
{
	char **args_ref;

	args_ref = args;
	if (!args)
		return (NULL);
	while (*args)
		parse_back_equals(*args++);
	return (args_ref);
}

void	str_erase_and_concat(char *dest, char const *src, size_t len)
{
	char buffer[BUFF];

	if (!dest || !src)
		return ;
	str_cpy(buffer, dest + len);
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
	str_cpy(dest, buffer);
}

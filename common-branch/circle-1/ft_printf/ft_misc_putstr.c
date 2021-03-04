/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft__misc_putstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:21:43 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:10:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, t_list *status)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		ft_putchar(str[i], status);
		i++;
	}
}

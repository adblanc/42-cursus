/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_special.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:04:06 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:10:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char_special(char c, t_list *status)
{
	ft_correct_flags(status);
	ft_print_padding(status, LEFT);
	ft_print_precision(status);
	if (c != '\0')
		ft_putchar(c, status);
	ft_print_padding(status, RIGHT);
}

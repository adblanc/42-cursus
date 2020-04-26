/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:32:25 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/02 18:35:01 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_intsize(unsigned int nb)
{
	size_t	size;

	size = 1;
	while (nb / 10)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

static void		ft_rec_itoa(char *str, unsigned int nb)
{
	if (nb / 10)
		ft_rec_itoa(str - 1, nb / 10);
	*str = nb % 10 + '0';
}

void			fill_itoa(char *str, int n)
{
	unsigned int	nb;
	int				minus;
	size_t			nbsize;

	minus = n < 0 ? 1 : 0;
	nb = n < 0 ? n * -1 : n;
	nbsize = ft_intsize(nb);
	if (minus)
		*str = '-';
	str[nbsize + minus] = '\0';
	ft_rec_itoa(&(str[nbsize + minus - 1]), nb);
}

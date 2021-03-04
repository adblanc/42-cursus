/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 10:23:20 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 10:23:24 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

char	*toUpperCase(char *s)
{
	char *ref;

	ref = s;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s >= 'a' && *s <= 'z')
			*s -= 32;
		s++;
	}
	return (ref);
}

int main(int ac, char **av) {
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
		while (*(++av))
			std::cout << toUpperCase(*av);
	std::cout << std::endl;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:26:25 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 19:10:24 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void)
{
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << "a : ";
	std::cout << a << std::endl;

	std::cout << "b : ";
	std::cout << b << std::endl;

	std::cout << "--- MAX ---" << std::endl;
	std::cout << Fixed::max(a, b) << std::endl;
	std::cout << Fixed::max(b, a) << std::endl;

	std::cout << "--- MIN ---" << std::endl;
	std::cout << Fixed::min(a, b) << std::endl;
	std::cout << Fixed::min(b, a) << std::endl;

	if (a < b)
		std::cout << "a < b" << std::endl;
	else
		std::cout << "a >= b" << std::endl;
	if (a <= b)
		std::cout << "a <= b" << std::endl;
	else
		std::cout << "a > b" << std::endl;
	if (a >= b)
		std::cout << "a >= b" << std::endl;
	else
		std::cout << "a < b" << std::endl;
	if (a != b)
		std::cout << "a != b" << std::endl;
	else
		std::cout << "a == b" << std::endl;
	if (a == b)
		std::cout << "a == b" << std::endl;
	else
		std::cout << "a != b" << std::endl;


	std::cout << "a - b : ";
	std::cout << a - b << std::endl;
	std::cout << "a + b : ";
	std::cout << a + b << std::endl;
	std::cout << "b / a : ";
	std::cout << b / a << std::endl;


	return 0;
}

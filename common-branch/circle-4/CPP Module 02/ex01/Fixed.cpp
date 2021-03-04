/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:57:04 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 18:10:45 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::bits = 8;

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	this->setRawBits(0);
}

Fixed::Fixed(const Fixed& copy)
{
	std::cout << "Copy constructor called" << std::endl;
	this->setRawBits(copy.getRawBits());
}

Fixed::Fixed(const int toConvert)
{
	std::cout << "Constructor int called" << std::endl;
	this->setRawBits((toConvert << this->bits));
}

Fixed::Fixed(const float toConvert)
{
	std::cout << "Constructor float called" << std::endl;
	this->setRawBits(roundf(toConvert * (1 << this->bits)));
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& obj)
{
	std::cout << "Assignation operator called" << std::endl;
	if (this != &obj)
		this->setRawBits(obj.getRawBits());
	return (*this);
}


void	Fixed::setRawBits(int raw)
{
	this->value = raw;
}

int		Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->value;
}

float	Fixed::toFloat(void) const
{
	return ((float)(this->value) / (1 << bits));
}

int		Fixed::toInt(void) const
{
	return ((int)(this->value >> bits));
}

std::ostream	&operator<<(std::ostream &output, Fixed const &value)
{
	output << value.toFloat();
	return output;
}

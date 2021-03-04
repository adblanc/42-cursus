/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:57:04 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 19:08:46 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::bits = 8;

Fixed::Fixed()
{
	this->setRawBits(0);
}

Fixed::Fixed(const Fixed& copy)
{
	this->setRawBits(copy.getRawBits());
}

Fixed::Fixed(const int toConvert)
{
	this->setRawBits((toConvert << this->bits));
}

Fixed::Fixed(const float toConvert)
{
	this->setRawBits(roundf(toConvert * (1 << this->bits)));
}

Fixed::~Fixed()
{
}

Fixed& Fixed::operator=(const Fixed& obj)
{
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

bool			Fixed::operator>(const Fixed &toCompare) const
{
	return (this->value > toCompare.value);
}

bool			Fixed::operator<(const Fixed &toCompare) const
{
	return (this->value < toCompare.value);
}

bool			Fixed::operator<=(const Fixed &toCompare) const
{
	return (this->value <= toCompare.value);
}

bool			Fixed::operator>=(const Fixed &toCompare) const
{
	return (this->value >= toCompare.value);
}

bool			Fixed::operator==(const Fixed &toCompare) const
{
	return (this->value == toCompare.value);
}

bool			Fixed::operator!=(const Fixed &toCompare) const
{
	return (this->value != toCompare.value);
}

Fixed			Fixed::operator+(const Fixed &toAdd) const
{
	return Fixed(this->toFloat() + toAdd.toFloat());
}

Fixed			Fixed::operator-(const Fixed &toSub) const
{
	return Fixed(this->toFloat() - toSub.toFloat());
}

Fixed			Fixed::operator*(const Fixed &toMul) const
{
	return Fixed(this->toFloat() * toMul.toFloat());
}

Fixed			Fixed::operator/(const Fixed &toDiv) const
{
	return Fixed(this->toFloat() / toDiv.toFloat());
}

Fixed			Fixed::operator++()
{
	this->value++;
	return (*this);
}

Fixed			Fixed::operator++(int)
{
	const Fixed old(*this);

	this->value++;
	return (old);
}

Fixed			Fixed::operator--(int)
{
	const Fixed old(*this);

	this->value--;
	return (old);
}

Fixed			Fixed::operator--()
{
	this->value -= 1;
	return (*this);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return a.value <= b.value ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return a.value >= b.value ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return a.value <= b.value ? a : b;
}

const Fixed &Fixed::max(const Fixed &a,const Fixed &b)
{
	return a.value >= b.value ? a : b;
}

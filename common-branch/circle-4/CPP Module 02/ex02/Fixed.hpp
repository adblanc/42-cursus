/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:56:53 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 19:08:44 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_H
# define FIXED_H

#include <iostream>
#include <cmath>

class Fixed {

	public:
	int		getRawBits(void) const;
	void	setRawBits(int const raw);


	Fixed();
	Fixed(const Fixed&);
	Fixed(const int toConvert);
	Fixed(const float toConvert);
	Fixed& operator=(const Fixed&);
	bool	operator>(const Fixed &toCompare) const;
	bool	operator<(const Fixed &toCompare) const;
	bool	operator<=(const Fixed &toCompare) const;
	bool	operator>=(const Fixed &toCompare) const;
	bool	operator==(const Fixed &toCompare) const;
	bool	operator!=(const Fixed &toCompare) const;
	Fixed	operator+(const Fixed &toAdd) const;
	Fixed	operator-(const Fixed &toSub) const;
	Fixed	operator*(const Fixed &toMul) const;
	Fixed	operator/(const Fixed &toDiv) const;
	Fixed	operator++();
	Fixed	operator++(int);
	Fixed	operator--();
	Fixed	operator--(int);
	static Fixed &min(Fixed &a, Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);
	static const Fixed &min(const Fixed &a, const Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);

	~Fixed();

	float	toFloat(void) const;
	int		toInt(void) const;

	private:
	int			value;
	static const int	bits;
};

std::ostream	&operator<<(std::ostream &output, Fixed const &value);



#endif

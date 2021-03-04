/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:56:53 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/18 15:31:02 by ablanc           ###   ########.fr       */
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
	~Fixed();

	float	toFloat(void) const;
	int		toInt(void) const;

	private:
	int			value;
	static const int	bits;
};

std::ostream	&operator<<(std::ostream &output, Fixed const &value);

#endif

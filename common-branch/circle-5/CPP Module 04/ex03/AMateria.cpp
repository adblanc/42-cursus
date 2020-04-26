/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 08:53:39 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 11:18:52 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(void)
{

};

AMateria::AMateria(std::string const &type)
{
	this->_type = type;
	this->_xp = 0;
};

AMateria::AMateria(const AMateria &src)
{
	*this = src;
};

AMateria::~AMateria()
{

};

AMateria &AMateria::operator= (const AMateria &rhs)
{
    if (this != &rhs)
    {
		this->_type = rhs._type;
		this->_xp = rhs._xp;
    }
    return (*this);
};

std::string const &AMateria::getType() const
{
	return this->_type;
};

unsigned int	AMateria::getXP() const
{
	return this->_xp;
}

void AMateria::use(ICharacter& target)
{
	(void) target;
	this->_xp += 10;
}

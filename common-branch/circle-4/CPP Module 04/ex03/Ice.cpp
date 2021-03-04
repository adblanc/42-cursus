/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:06:28 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 11:20:00 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(void): AMateria("ice")
{

};

Ice::~Ice()
{

};

Ice::Ice(const Ice &src): AMateria(src.getType())
{
	*this = src;
};

Ice &Ice::operator= (const Ice &rhs)
{
    (void)rhs;
    return (*this);
};

void	Ice::use(ICharacter &target)
{
	AMateria::use(target);
	std::cout << "* shoots an ice bolet at " + target.getName() + " *" << std::endl;
}

Ice *Ice::clone() const
{
	return (new Ice(*this));
}

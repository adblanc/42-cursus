/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:06:53 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 11:19:50 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(void): AMateria("cure")
{

};

Cure::~Cure(void)
{

};

Cure::Cure(const Cure &src): AMateria(src.getType())
{
	*this = src;
};

Cure &Cure::operator= (const Cure &rhs)
{
    (void)rhs;
    return (*this);
};

void	Cure::use(ICharacter &target)
{
	AMateria::use(target);
	std::cout << "* heals " + target.getName() + "'s wounds *" << std::endl;
}

Cure *Cure::clone() const
{
	return (new Cure(*this));
}

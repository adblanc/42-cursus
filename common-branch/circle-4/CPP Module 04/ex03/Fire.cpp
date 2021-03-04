/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fire.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:06:28 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 10:14:07 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fire.hpp"

Fire::Fire(void): AMateria("fire")
{

};

Fire::~Fire()
{

};

Fire::Fire(const Fire &src): AMateria(src.getType())
{
	*this = src;
};

Fire &Fire::operator= (const Fire &rhs)
{
    (void)rhs;
    return (*this);
};

void	Fire::use(ICharacter &target)
{
	AMateria::use(target);
	std::cout << "* burn " + target.getName() + " in fucking hell *" << std::endl;
}

Fire *Fire::clone() const
{
	return (new Fire(*this));
}

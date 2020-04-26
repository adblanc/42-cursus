/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperMutant.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:47:09 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 18:53:55 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMutant.hpp"

SuperMutant::SuperMutant(void) : Enemy(170, "Super Mutant")
{
	std::cout << "Gaaah. Me want smash heads!" << std::endl;
};

SuperMutant::SuperMutant(const SuperMutant &src): Enemy(src.hp, src.type)
{
	*this = src;
};

SuperMutant::~SuperMutant(void)
{
	std::cout << "Aaargh ..." << std::endl;
};

SuperMutant &SuperMutant::operator= (const SuperMutant &rhs)
{
	if (this != &rhs)
	{
		this->hp = rhs.hp;
		this->type = rhs.type;
	}
	return (*this);
};

void	SuperMutant::takeDamage(int dmg) {
	dmg -= 3;
	Enemy::takeDamage(dmg);
}

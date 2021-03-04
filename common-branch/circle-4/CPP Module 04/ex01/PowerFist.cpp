/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PowerFist.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:45:05 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 15:47:23 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PowerFist.hpp"

PowerFist:: PowerFist(void): AWeapon("Power First", 8, 50) {
}

PowerFist::PowerFist(const PowerFist &s): AWeapon(s.name, s.apCost, s.damage) {
	*this = s;
}

PowerFist::~PowerFist(void) {
}

PowerFist &PowerFist::operator=(const PowerFist &s) {
	if (this != &s) {
		this->name = s.name;
		this->apCost = s.apCost;
		this->damage = s.damage;
	}
	return (*this);
}

void	PowerFist::attack(void) const {
	std::cout << "* pschhh... SBAM ! *" << std::endl;
}

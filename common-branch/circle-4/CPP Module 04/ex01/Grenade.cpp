/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grenade.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:11:13 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 15:44:50 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Grenade.hpp"

Grenade:: Grenade(void): AWeapon("Grenade", 2, 5) {
}

Grenade::Grenade(const Grenade &s): AWeapon(s.name, s.apCost, s.damage) {
	*this = s;
}

Grenade::~Grenade(void) {
}

Grenade &Grenade::operator=(const Grenade &s) {
	if (this != &s) {
		this->name = s.name;
		this->apCost = s.apCost;
		this->damage = s.damage;
	}
	return (*this);
}

void	Grenade::attack(void) const {
	std::cout << "Grenada !!!!!!!!!!!" << std::endl;
}

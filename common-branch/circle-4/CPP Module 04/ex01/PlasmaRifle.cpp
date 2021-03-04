/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlasmaRifle.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:11:13 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 19:14:43 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PlasmaRifle.hpp"

PlasmaRifle:: PlasmaRifle(void): AWeapon("Plasma Rifle", 5, 21) {
}

PlasmaRifle::PlasmaRifle(const PlasmaRifle &s): AWeapon(s.name, s.apCost, s.damage) {
	*this = s;
}

PlasmaRifle::~PlasmaRifle(void) {
}

PlasmaRifle &PlasmaRifle::operator=(const PlasmaRifle &s) {
	if (this != &s) {
		this->name = s.name;
		this->apCost = s.apCost;
		this->damage = s.damage;
	}
	return (*this);
}

void	PlasmaRifle::attack(void) const {
	std::cout << "* piouuu piouuu piouuu *" << std::endl;
}

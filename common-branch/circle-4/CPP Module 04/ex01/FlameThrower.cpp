/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlameThrower.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:11:13 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 15:44:50 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FlameThrower.hpp"

FlameThrower:: FlameThrower(void): AWeapon("FlameThrower", 10, 50) {
}

FlameThrower::FlameThrower(const FlameThrower &s): AWeapon(s.name, s.apCost, s.damage) {
	*this = s;
}

FlameThrower::~FlameThrower(void) {
}

FlameThrower &FlameThrower::operator=(const FlameThrower &s) {
	if (this != &s) {
		this->name = s.name;
		this->apCost = s.apCost;
		this->damage = s.damage;
	}
	return (*this);
}

void	FlameThrower::attack(void) const {
	std::cout << "shhhhhhhhhhhhhhhh" << std::endl;
}

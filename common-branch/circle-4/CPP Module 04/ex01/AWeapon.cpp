/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:11:22 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 16:43:25 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AWeapon.hpp"

AWeapon:: AWeapon(void) {
	this->name = "Arme de base";
	this->apCost = 10;
	this->damage = 10;
}

AWeapon::AWeapon(std::string const &name, int apcost, int damage) {
	this->name = name;
	this->apCost = apcost;
	this->damage = damage;
}

AWeapon::AWeapon(const AWeapon &s) {
	*this = s;
}

AWeapon & AWeapon::operator=(const AWeapon &s) {
	if (this != &s) {
		this->apCost = s.apCost;
		this->damage = s.damage;
		this->name = s.name;
	}
	return *this;
}

AWeapon::~AWeapon(void) {
	std::cout << this->name + " detruite." << std::endl;
}

std::string const AWeapon::getName() const {
	return this->name;
}

int	AWeapon::getAPCost() const {
	return this->apCost;
}

int	AWeapon::getDamage() const {
	return this->damage;
}



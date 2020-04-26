/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:12:29 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 21:57:07 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {

	std::cout << "Booting sequence complete. Hello! I am your new steward bot. Designation: CL4P-TP, Hyperion Robot, Class C. Please adjust factory settings to meet your needs before deployment." << std::endl;
}

ClapTrap::~ClapTrap() {

	std::cout << "I'M DEAD I'M DEAD OHMYGOD I'M DEAD!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	int value;
	int dmg;
	std::stringstream ssDmg;
	std::stringstream ssValue;

	dmg = amount - this->armorReduction;
	value = this->hitPoints - dmg;
	ssDmg << dmg;

	if (value < 0)
		value = 0;
	if (value > this->maxHitPoints)
		value = this->maxHitPoints;
	ssValue << value;

	std::cout << this->name + " a prit " + ssDmg.str() + " points de dégâts, il lui reste " + ssValue.str() + " pdv." << std::endl;

	this->hitPoints = value;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	int value;
	std::stringstream ssHeal;
	std::stringstream ssValue;

	ssHeal << amount;
	value = this->hitPoints + amount;

	if (value < 0)
		value = 0;
	if (value > this->maxHitPoints)
		value = this->maxHitPoints;
	ssValue << value;

	std::cout << this->name + " se soigne  " + ssHeal.str() + " points de dégâts, il a alors " + ssValue.str() + " pdv." << std::endl;

	this->hitPoints = value;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NinjaTrap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:29:20 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 22:49:33 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NinjaTrap.hpp"

NinjaTrap::NinjaTrap(std::string const & name) {
	this->name = name;
	this->hitPoints = 60;
	this->energyPoints = 120;
	this->maxEnergyPoints = 120;
	this->maxHitPoints = 60;
	this->level = 1;
	this->meleeDamage = 60;
	this->rangeDamage = 5;
	this->armorReduction = 0;

	std::cout << "Hey everybody! Check out my package!" << std::endl;
}

NinjaTrap::~NinjaTrap() {

	std::cout << "I'm flying! I'm really flying!" << std::endl;
}

void	NinjaTrap::rangedAttack(std::string const & target) {
	std::stringstream ss;
	ss << this->rangeDamage;
	std::cout << "NINJ4-TP " + this->name + " attaque " + target + " à distance, causant " + ss.str() + "  points de dégâts !" << std::endl;
}

void	NinjaTrap::meleeAttack(std::string const & target) {
	std::stringstream ss;
	ss << this->meleeDamage;
	std::cout << "NINJ4-TP " + this->name + " attaque " + target + " au cac, causant " + ss.str() + "  points de dégâts !" << std::endl;
}

void	NinjaTrap::ninjaShoebox(ScavTrap &scav) {
	std::cout << "NinjaShoeBox sur " + scav.name + ",c'est un coup de cac !" << std::endl;
	scav.takeDamage(this->meleeDamage);
}

void	NinjaTrap::ninjaShoebox(FragTrap &frag) {
	std::cout << "NinjaShoeBox sur " + frag.name + ",c'est un air KO a distance !" << std::endl;
	frag.takeDamage(this->rangeDamage);
}

void	NinjaTrap::ninjaShoebox(NinjaTrap &ninja) {
	std::cout << "NinjaShoeBox sur " + ninja.name + "c'est un OS!" << std::endl;
	ninja.takeDamage(1000);
}

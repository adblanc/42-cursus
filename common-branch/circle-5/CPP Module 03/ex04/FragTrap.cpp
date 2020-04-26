/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 08:53:00 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 22:57:06 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(void) {
	return ;
}

FragTrap::FragTrap(std::string const & name) {
	this->name = name;
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->maxEnergyPoints = 100;
	this->maxHitPoints = 100;
	this->level = 1;
	this->meleeDamage = 30;
	this->rangeDamage = 20;
	this->armorReduction = 5;
	srand(time(NULL));

	std::cout << "Success! My spell to make you want to hang out with me worked!" << std::endl;
}

FragTrap::~FragTrap() {

	std::cout << "Stay a while, and listen. Oh god, please -- PLEASE! -- stay a while" << std::endl;
}

void	FragTrap::rangedAttack(std::string const & target) {
	std::stringstream ss;
	ss << this->rangeDamage;
	std::cout << "FR4G-TP " + this->name + " attaque " + target + " à distance, causant " + ss.str() + "  points de dégâts !" << std::endl;
}

void	FragTrap::meleeAttack(std::string const & target) {
	std::stringstream ss;
	ss << this->meleeDamage;
	std::cout << "FR4G-TP " + this->name + " attaque " + target + " au cac, causant " + ss.str() + "  points de dégâts !" << std::endl;
}

int		FragTrap::vaulthunter_dot_exe(std::string const & target) {
	std::string attacks[] = {"Lancer de nouille", "Balayette laser", "Pichnette", "Cravatte", "Ouragan"};
	if (this->energyPoints < 25) {
		std::cout << "Impossible de lancer l'attaque, pas assez d'energie." << std::endl;
		return (0);
	}
	this->energyPoints -= 25;
	if (this->energyPoints < 0)
		this->energyPoints = 0;
	std::cout << "FR4G-TP " + this->name + " attaque " + target + " avec " + attacks[std::rand() % 5] << std::endl;
	return (1);
}

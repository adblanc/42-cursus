/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:52:36 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 21:58:45 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string const & name) {
	this->name = name;
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->maxEnergyPoints = 50;
	this->maxHitPoints = 100;
	this->level = 1;
	this->meleeDamage = 20;
	this->rangeDamage = 15;
	this->armorReduction = 3;
	srand(time(NULL));

	std::cout << "Yes. Remember what? Are... are you my father?" << std::endl;
}

ScavTrap::~ScavTrap() {

	std::cout << "Are you god? Am I dead?" << std::endl;
}

void	ScavTrap::rangedAttack(std::string const & target) {
	std::stringstream ss;
	ss << this->rangeDamage;
	std::cout << "SC4V-TP " + this->name + " attaque " + target + " à distance, causant " + ss.str() + "  points de dégâts !" << std::endl;
}

void	ScavTrap::meleeAttack(std::string const & target) {
	std::stringstream ss;
	ss << this->meleeDamage;
	std::cout << "SC4V-TP " + this->name + " attaque " + target + " au cac, causant " + ss.str() + "  points de dégâts !" << std::endl;
}

void		ScavTrap::challengeNewcomer() {
	std::string challenges[] = {"Jongler avec ses pieds", "Prendre la ligne 13 aux heures de pointe", "Se presenter aux presidentielles", "Faire la piscine de 42"};

	std::cout << "Challenge : " + challenges[std::rand() % 4] << std::endl;
}

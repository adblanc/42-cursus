/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperTrap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:15:00 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/06 12:40:10 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperTrap.hpp"

SuperTrap::SuperTrap(std::string const & name) {
    this->name = name;
    this->hitPoints = 100;
    this->energyPoints = 120;
    this->maxEnergyPoints = 120;
    this->level = 1;
    this->meleeDamage = 60;
    this->rangeDamage = 20;
    this->armorReduction = 0;
    
    std::cout << "Initialisation du SuPeR D4RK Tr4p" << std::endl;
}

SuperTrap::~SuperTrap() {
    std::cout << "Destruction SuperTrap...." << std::endl;
}

void	SuperTrap::rangedAttack(std::string const & target) {
    return FragTrap::rangedAttack(target);
}

void	SuperTrap::meleeAttack(std::string const & target) {
    return NinjaTrap::meleeAttack(target);
}
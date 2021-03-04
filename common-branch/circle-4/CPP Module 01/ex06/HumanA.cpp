/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:37:09 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 16:43:56 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon): weapon(weapon)
{
	this->setName(name);
};

void	HumanA::setName(std::string name)
{
	this->name = name;
}

void	HumanA::attack()
{
	std::cout << this->name + " attacks with " + this->weapon.getType() << std::endl;
}

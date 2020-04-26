/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:23:14 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 16:07:45 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type)
{
	setType(type);
}

void	Weapon::setType(std::string type)
{
	this->type = type;
}

const std::string &Weapon::getType()
{
	const std::string &ref = this->type;
	return ref;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:02:35 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 07:10:56 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	Zombie::setName(std::string s)
{
	name = s;
}

void	Zombie::setType(std::string s)
{
	type = s;
}

std::string	Zombie::getName()
{
	return name;
}

std::string	Zombie::getType()
{
	return type;
}

void	Zombie::advert()
{
	std::cout << "<" + name + " (" + type + ")>" + "Braiiiiiiiinnssss !!!" << std::endl;
}

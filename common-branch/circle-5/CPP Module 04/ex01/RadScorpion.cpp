/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RadScorpion.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:55:13 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 18:54:37 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RadScorpion.hpp"

RadScorpion::RadScorpion(void): Enemy(80, "RadScorpion")
{
	std::cout << "* click click click *" << std::endl;
};

RadScorpion::RadScorpion(const RadScorpion &src): Enemy(src.hp, src.type)
{
	*this = src;
};

RadScorpion::~RadScorpion(void)
{
	std::cout << "* SPROTCH *" << std::endl;
};

RadScorpion &RadScorpion::operator= (const RadScorpion &rhs)
{
	if (this != &rhs)
	{
		this->hp = rhs.hp;
		this->type = rhs.type;
	}
	return (*this);
};

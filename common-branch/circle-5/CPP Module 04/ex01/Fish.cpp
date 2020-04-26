/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fish.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:55:13 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 18:54:37 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fish.hpp"

Fish::Fish(void): Enemy(99, "Fish")
{
	std::cout << "hi I am a fish" << std::endl;
};

Fish::Fish(const Fish &src): Enemy(src.hp, src.type)
{
	*this = src;
};

Fish::~Fish(void)
{
	std::cout << "* DROWNING *" << std::endl;
};

Fish &Fish::operator= (const Fish &rhs)
{
	if (this != &rhs)
	{
		this->hp = rhs.hp;
		this->type = rhs.type;
	}
	return (*this);
};

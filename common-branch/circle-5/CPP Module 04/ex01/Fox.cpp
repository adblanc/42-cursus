/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fox.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:55:13 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 18:54:37 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fox.hpp"

Fox::Fox(void): Enemy(99, "Fox")
{
	std::cout << "hi I am a Fox" << std::endl;
};

Fox::Fox(const Fox &src): Enemy(src.hp, src.type)
{
	*this = src;
};

Fox::~Fox(void)
{
	std::cout << "* run *" << std::endl;
};

Fox &Fox::operator= (const Fox &rhs)
{
	if (this != &rhs)
	{
		this->hp = rhs.hp;
		this->type = rhs.type;
	}
	return (*this);
};

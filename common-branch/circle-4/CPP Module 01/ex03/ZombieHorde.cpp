/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:31:18 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/06 09:41:25 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieHorde.hpp"

ZombieHorde::ZombieHorde(int n)
{
	srand(time(NULL));
	std::string names[] = {"Jean", "Henri", "Aria",
	 "Mathis", "Leo", "Paul", "Alex", "Anna",
	  "Lou", "Louis", "Maxime", "Florian", "Marc"};

	horde = new Zombie[n];
	for (int i = 0; i < n ; i++) {
		horde[i].setType("Type eau");
		horde[i].setName(names[std::rand() % 13]);
	}
	hordeNbr = n;
}

ZombieHorde::~ZombieHorde()
{
	delete[] horde;
}

void	ZombieHorde::advert()
{
	for (int i = 0; i < hordeNbr ; i++)
		horde[i].advert();
}

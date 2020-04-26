/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:02:53 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 13:14:46 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieEvent.hpp"
#include "stdlib.h"

void	ZombieEvent::setZombieType(std::string value)
{
	zombieType = value;
}

Zombie *ZombieEvent::newZombie(std::string name)
{
	Zombie *newZombie;

	newZombie = new Zombie;
	newZombie->setType(zombieType);
	newZombie->setName(name);

	return newZombie;
}

Zombie *ZombieEvent::randomChump()
{
	std::string names[] = {"Jean", "Henri", "Aria",
	 "Mathis", "Leo", "Paul", "Alex", "Anna",
	  "Lou", "Louis", "Maxime", "Florian", "Marc"};
	Zombie *newZombie;

	newZombie = ZombieEvent::newZombie(names[std::rand() % 13]);
	newZombie->advert();
	return newZombie;
}

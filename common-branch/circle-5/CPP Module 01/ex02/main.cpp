/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:03:05 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 13:16:57 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieEvent.hpp"

int main()
{
	ZombieEvent events;
	Zombie	boss;
	Zombie *zombies[5];

	std::cout << "First wave..." << std::endl << std::endl;
	events.setZombieType("Type feu");
	for (int i = 0; i < 5 ; i++)
		zombies[i] = events.randomChump();

	std::cout << std::endl << "First zombie mutation" << std::endl;
	std::cout << zombies[0]->getName() << " of type " + zombies[0]->getType() + " become" << std::endl;
	zombies[0]->setType("Type air");
	zombies[0]->setName("ZombieStyle");
	zombies[0]->advert();

	for (int i = 0; i < 5; i++)
		delete zombies[i];
		
	std::cout << "End of the first wave.." << std::endl;
	std::cout << "Zombie Boss appear !" << std::endl;
	boss.setName("ZombieBoss");
	boss.setType("PointFaibleTropFort");
	boss.advert();
	std::cout << "End." << std::endl;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:02:59 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 07:23:53 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_EVENT_H
# define ZOMBIE_EVENT_H
#include "Zombie.hpp"

class ZombieEvent
{
	public:

	void	setZombieType(std::string value);
	Zombie *newZombie(std::string name);
	Zombie *randomChump();

	private:

	std::string zombieType;
};

#endif

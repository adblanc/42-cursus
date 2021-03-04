/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:31:25 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 14:16:49 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HORDE_H
# define ZOMBIE_HORDE_H

#include "Zombie.hpp"

class ZombieHorde {

	public:

	~ZombieHorde();
	ZombieHorde(int n);
	void	advert();

	private:
	Zombie *horde;
	int		hordeNbr;

};

#endif

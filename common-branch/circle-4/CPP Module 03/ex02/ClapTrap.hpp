/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:09:30 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 22:47:41 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

#include <iostream>
#include <sstream>

class ClapTrap {

	public:

	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);

	ClapTrap();
	~ClapTrap();

	protected:

	int hitPoints;
	int maxHitPoints;
	int energyPoints;
	int maxEnergyPoints;
	int level;
	std::string name;
	int	meleeDamage;
	int	rangeDamage;
	int	armorReduction;

};


#endif

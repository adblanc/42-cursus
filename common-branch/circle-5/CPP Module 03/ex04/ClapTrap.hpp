/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:09:30 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/06 12:28:44 by ablanc           ###   ########.fr       */
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

	std::string name;
	protected:

	int hitPoints;
	int maxHitPoints;
	int energyPoints;
	int maxEnergyPoints;
	int level;
	int	meleeDamage;
	int	rangeDamage;
	int	armorReduction;

};


#endif

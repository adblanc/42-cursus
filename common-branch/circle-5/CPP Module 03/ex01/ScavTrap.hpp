/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:50:03 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/06 09:58:16 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

#include <iostream>
#include <sstream>

class ScavTrap {

	public:

	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);

	void	challengeNewcomer(void);

	ScavTrap(std::string const & name);
	~ScavTrap();

	private:

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:50:03 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 22:48:44 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

#include "ClapTrap.hpp"

#include <iostream>
#include <sstream>

class ScavTrap: public ClapTrap {

	public:

	void	challengeNewcomer(void);
	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);

	ScavTrap(std::string const & name);
	~ScavTrap();

};


#endif

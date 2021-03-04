/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NinjaTrap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:27:44 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/06 12:35:39 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NINJA_TRAP_HPP
# define NINJA_TRAP_HPP

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class NinjaTrap: virtual public ClapTrap {

	public:

	NinjaTrap(void);
	NinjaTrap(std::string const & name);
	~NinjaTrap();
	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);

	void	ninjaShoebox(FragTrap &frag);
	void	ninjaShoebox(ScavTrap &scav);
	void	ninjaShoebox(NinjaTrap &ninja);

};


#endif

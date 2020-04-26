/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 08:54:05 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/06 12:35:28 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

#include "ClapTrap.hpp"

#include <iostream>
#include <sstream>

class FragTrap : virtual public ClapTrap  {

	public:
	
	int		vaulthunter_dot_exe(std::string const & target);
	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);

	FragTrap(void);
	FragTrap(std::string const & name);

	~FragTrap();
};

#endif

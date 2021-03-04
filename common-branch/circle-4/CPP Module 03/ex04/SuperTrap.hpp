/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperTrap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:06:38 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/06 12:35:58 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPER_TRAP_HPP
# define SUPER_TRAP_HPP

#include "NinjaTrap.hpp"
#include "FragTrap.hpp"

class SuperTrap: public FragTrap, public NinjaTrap {
    public:

    SuperTrap(std::string const & name);
    ~SuperTrap();

    
	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);

};


#endif
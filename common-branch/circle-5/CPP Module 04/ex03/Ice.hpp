/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:06:20 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 10:12:17 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

#include "AMateria.hpp"

#include <iostream>

class Ice: public AMateria
{
	public:
		Ice(void);
		Ice(const Ice &src);
		Ice &operator=(const Ice &rhs);
		virtual ~Ice();

		virtual Ice* clone() const;
		virtual void use(ICharacter& target);
};


#endif

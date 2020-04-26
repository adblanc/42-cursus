/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fire.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:06:20 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 10:12:17 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIRE_HPP
# define FIRE_HPP

#include "AMateria.hpp"

#include <iostream>

class Fire: public AMateria
{
	public:
		Fire(void);
		Fire(const Fire &src);
		Fire &operator=(const Fire &rhs);
		virtual ~Fire();

		virtual Fire* clone() const;
		virtual void use(ICharacter& target);
};


#endif

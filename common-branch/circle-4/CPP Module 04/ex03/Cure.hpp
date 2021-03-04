/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:03:17 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 10:15:09 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

#include "AMateria.hpp"

#include <iostream>

class Cure: public AMateria
{
	public:
		Cure(void);
		Cure(const Cure &src);
		Cure &operator=(const Cure &rhs);
		virtual ~Cure();

		virtual Cure* clone() const;
		virtual void use(ICharacter& target);
};


#endif

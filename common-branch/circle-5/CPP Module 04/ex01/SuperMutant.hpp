/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperMutant.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:45:22 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 16:49:54 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPERMUTANT_HPP
# define SUPERMUTANT_HPP

#include <iostream>
#include <string>
#include "Enemy.hpp"

class SuperMutant : public Enemy
{
	public:
		SuperMutant(void);
		SuperMutant(const SuperMutant &src);
		~SuperMutant(void);

SuperMutant	&operator=(const SuperMutant &rhs);

		virtual void	takeDamage(int dmg);

	private:

};


 #endif

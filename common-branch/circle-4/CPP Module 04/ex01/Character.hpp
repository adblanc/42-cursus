/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:30:25 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 17:26:59 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include <string>
#include <iostream>
#include <sstream>
#include "AWeapon.hpp"
#include "Enemy.hpp"

class Character
{
	public:
		Character(void);
		Character(std::string const &name);
		Character(const Character &src);
		~Character(void);

		void	recoverAP();
		void	equip(AWeapon *);
		void	attack(Enemy *);
		std::string const getName() const;
		int getAp(void) const;
		std::string const getWeaponName() const;

Character	&operator=(const Character &rhs);

	private:

	std::string name;
	int			pa;
	AWeapon		*weapon;

};

std::ostream &operator<<(std::ostream &, const Character &);

 #endif

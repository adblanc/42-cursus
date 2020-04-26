/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:04:43 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 16:43:11 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AWEAPON_HPP
# define AWEAPON_HPP

#include <string>
#include <iostream>

class AWeapon {
	protected:
		std::string name;
		int apCost;
		int damage;

	public:

		AWeapon(void);
		AWeapon(const AWeapon &);
		virtual ~AWeapon(void);
		AWeapon &operator=(const AWeapon &);

		AWeapon(std::string const &name, int apcost, int damage);

	//get methods
		std::string const getName(void) const;
		int getAPCost() const;
		int getDamage() const;

		virtual void attack() const = 0;

};


#endif

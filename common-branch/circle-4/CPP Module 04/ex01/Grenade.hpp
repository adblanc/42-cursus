/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grenade.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:53:11 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 15:33:11 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRENADE_HPP
# define GRENADE_HPP

#include "AWeapon.hpp"

class Grenade: public AWeapon {

	public:

		Grenade(void);
		Grenade(const Grenade &);
		~Grenade(void);
		Grenade &operator=(const Grenade &);

		virtual void attack(void) const;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlasmaRifle.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:53:11 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 15:33:11 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLASMARIFLE_HPP
# define PLASMARIFLE_HPP

#include "AWeapon.hpp"

class PlasmaRifle: public AWeapon {

	public:

		PlasmaRifle(void);
		PlasmaRifle(const PlasmaRifle &);
		~PlasmaRifle(void);
		PlasmaRifle &operator=(const PlasmaRifle &);

		virtual void attack(void) const;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlameThrower.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:53:11 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 15:33:11 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAMETHROWER_HPP
# define FLAMETHROWER_HPP

#include "AWeapon.hpp"

class FlameThrower: public AWeapon {

	public:

		FlameThrower(void);
		FlameThrower(const FlameThrower &);
		~FlameThrower(void);
		FlameThrower &operator=(const FlameThrower &);

		virtual void attack(void) const;
};

#endif

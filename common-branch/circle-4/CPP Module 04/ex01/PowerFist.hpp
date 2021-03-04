/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PowerFist.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:42:43 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 15:44:05 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWERFIST_HPP
# define POWERFIST_HPP

#include "AWeapon.hpp"

class PowerFist: public AWeapon {

	public:

		PowerFist(void);
		PowerFist(const PowerFist &);
		~PowerFist(void);
		PowerFist &operator=(const PowerFist &);

		virtual void attack(void) const;
};

#endif

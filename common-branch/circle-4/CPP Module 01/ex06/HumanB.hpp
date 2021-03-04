/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:37:37 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 16:47:50 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HUMAN_B_H
# define HUMAN_B_H
#include "Weapon.hpp"

class HumanB
{

	public:
	HumanB(std::string name);
	void	attack();
	void	setName(std::string name);
	void	setWeapon(Weapon &weapon);

	private:
	Weapon *weapon;
	std::string name;

};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:37:28 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 16:44:01 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_A_H
# define HUMAN_A_H
#include "Weapon.hpp"

class HumanA
{

	public:
	HumanA(std::string name, Weapon &weapon);
	void	setName(std::string name);

	void	attack();

	private:
	Weapon &weapon;
	std::string name;

};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:33:57 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 21:45:04 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main() {
	FragTrap robot("Digidix");

	robot.meleeAttack("John");
	robot.rangedAttack("Caprisun");

	robot.takeDamage(25);
	robot.takeDamage(90);
	robot.beRepaired(150);

	robot.vaulthunter_dot_exe("Kevin");
	robot.vaulthunter_dot_exe("Kevin");
	robot.vaulthunter_dot_exe("Kevin");
	robot.vaulthunter_dot_exe("Kevin");
	robot.vaulthunter_dot_exe("Kevin");

	return (0);
}

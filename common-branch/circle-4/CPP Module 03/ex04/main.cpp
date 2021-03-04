/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:33:57 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 22:57:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "NinjaTrap.hpp"
#include "SuperTrap.hpp"

int main() {
	FragTrap robot("Digidix");
	ScavTrap bg("Street");
	NinjaTrap ok("Lowkey");
	SuperTrap michael("Michael");

	robot.meleeAttack("John");
	robot.rangedAttack("Caprisun");

	robot.takeDamage(25);
	robot.takeDamage(90);
	robot.beRepaired(150);

	robot.vaulthunter_dot_exe("Kevin");

	bg.meleeAttack("John");
	bg.rangedAttack("Caprisun");

	bg.takeDamage(25);
	bg.takeDamage(90);
	bg.beRepaired(150);

	bg.challengeNewcomer();

	ok.meleeAttack("John");
	ok.rangedAttack("Caprisun");

	ok.takeDamage(25);
	ok.takeDamage(90);
	ok.beRepaired(150);

	michael.meleeAttack("John");
	michael.rangedAttack("Caprisun");

	michael.ninjaShoebox(robot);
	michael.ninjaShoebox(bg);
	michael.ninjaShoebox(ok);

	michael.vaulthunter_dot_exe("Bogota");
	michael.vaulthunter_dot_exe("Bogota");
	michael.vaulthunter_dot_exe("Bogota");
	michael.vaulthunter_dot_exe("Bogota");
	michael.vaulthunter_dot_exe("Bogota");


	return (0);
}

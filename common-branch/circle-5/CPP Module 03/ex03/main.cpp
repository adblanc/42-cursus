/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:33:57 by ablanc            #+#    #+#             */
/*   Updated: 2020/02/27 22:39:09 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "NinjaTrap.hpp"

int main() {
	FragTrap robot("Digidix");
	ScavTrap bg("Street");
	NinjaTrap ok("Lowkey");

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

	ok.ninjaShoebox(robot);
	ok.ninjaShoebox(bg);
	ok.ninjaShoebox(ok);

	return (0);
}

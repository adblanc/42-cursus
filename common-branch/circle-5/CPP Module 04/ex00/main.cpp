/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:29:50 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 17:46:16 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorcerer.hpp"
#include "Victim.hpp"
#include "Peon.hpp"
#include "Athlete.hpp"
#include "Baker.hpp"

int main()
{
	Sorcerer robert("Robert", "the Magnificient");

	Victim jim("Jimmy");
	Peon joe("Joe");
	Baker luc("Luc");
	Athlete jean("Jean");


	std::cout << robert << jim << joe << luc << jean;

	robert.polymorph(jim);
	robert.polymorph(joe);
	robert.polymorph(luc);
	robert.polymorph(jean);

	jim.getPolymorphed();
	joe.getPolymorphed();
	jean.getPolymorphed();
	luc.getPolymorphed();

	return (0);
}

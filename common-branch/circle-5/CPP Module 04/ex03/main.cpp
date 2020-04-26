/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:09:58 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 12:28:55 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Character.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Fire.hpp"
#include <sstream>

int main()
{
	std::stringstream ss;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");


	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);



	ICharacter* bob = new Character("bob");

	ss << tmp->getXP();
	std::cout << "Metaria 1, xp : " + ss.str() << std::endl;
	ss.str("");
	me->use(0, *bob);
	me->use(1, *bob);

	ss << tmp->getXP();
	std::cout << "Metaria 1, xp : " + ss.str() << std::endl;
	ss.str("");

	tmp = src->createMateria("fire");
	if (!tmp)
	{
		std::cout << "On a pas encore de materia fire connue" << std::endl;
		me->equip(tmp);
		me->use(-1, *bob);
		me->use(5, *bob);
	}

	src->learnMateria(new Fire());
	tmp = src->createMateria("fire");
	me->equip(tmp);
	me->use(2, *bob);
	std::cout << "Materia 2, type: " + tmp->getType() << std::endl;

	AMateria *tmp_2 = tmp->clone();
	AMateria *tmp_3 = tmp->clone();

	std::cout << "Materia 2 clone, type: " + tmp_2->getType() << std::endl;

	me->equip(tmp_2);
	me->use(3, *bob);

	me->equip(tmp_3);
	me->use(3, *bob);

	ss << tmp_3->getXP();
	std::cout << "Metaria tmp_3, xp : " + ss.str() << std::endl;
	ss.str("");



	delete bob;
	delete me;
	delete src;

	return 0;
}

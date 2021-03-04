/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:30:41 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 18:57:19 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(void)
{
	this->pa = 40;
	this->name = "Character de base";
	this->weapon = NULL;
};

Character::Character(std::string const & name) {
	this->pa = 40;
	this->name = name;
	this->weapon = NULL;
}

Character::Character(const Character &src)
{
	*this = src;
};

Character::~Character(void)
{

};

Character &Character::operator= (const Character &rhs)
{
	if (this != &rhs)
	{
		this->name = rhs.name;
		this->pa = rhs.pa;
		this->weapon = rhs.weapon;
	}
	return (*this);
};

void	Character::recoverAP(void) {
	if (this->pa + 10 > 40)
		this->pa = 40;
	else
		this->pa += 10;
}

void	Character::attack(Enemy *enemy) {
	if (!this->weapon || this->pa - this->weapon->getAPCost() < 0)
		return ;

	this->pa -= this->weapon->getAPCost();

	std::cout << this->name + " attaque " + enemy->getType() + " with a " + this->weapon->getName() << std::endl;

	this->weapon->attack();

	enemy->takeDamage(this->weapon->getDamage());
	if (enemy->getHP() <= 0)
		delete (enemy);
}

void	Character::equip(AWeapon *weapon) {
	this->weapon = weapon;
}

int	Character::getAp(void) const {
	return this->pa;
}

std::string const Character::getName(void) const {
	return this->name;
}

std::string const Character::getWeaponName(void) const {
	if (this->weapon) {
		return this->weapon->getName();
	}
	else
		return "";
}

std::ostream &operator<<(std::ostream &out, const Character &c) {
	std::stringstream ss;
	std::string weapon;

	weapon = c.getWeaponName();
	ss << c.getAp();
	if (weapon.empty())
		out << c.getName() + " has " + ss.str() + " AP and is unarmed" << std::endl;
	else
		out << c.getName() + " has " + ss.str() + " AP and carries a " + weapon << std::endl;
	return out;
}

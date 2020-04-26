/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:22:44 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 10:20:17 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(void)
{

};

void Character::_deepCopy(const Character &s)
{
	this->name = s.name;
	for (int i = 0; i < 4 ; i++) {
		delete this->inventory[i];
		if (s.inventory[i])
			this->inventory[i] = s.inventory[i]->clone();
		else
			this->inventory[i] = NULL;
		}
};

Character::Character(std::string const &name)
{
	this->name = name;
	for (int i = 0; i < 4 ; i++)
		this->inventory[i] = NULL;
};

Character::Character(const Character &src)
{
	this->_deepCopy(src);
};

Character::~Character()
{
	for (int i = 0; i < 4; i++)
		delete this->inventory[i];
};

Character &Character::operator= (const Character &rhs)
{
    if (this != &rhs)
		this->_deepCopy(rhs);
    return (*this);
};

void	Character::equip(AMateria *m)
{
	int i;

	i = 0;
	while (i < 4 && this->inventory[i])
		i++;
	if (i == 4)
		return ;
	this->inventory[i] = m;
};

void	Character::unequip(int idx)
{
	if (idx >= 4 || idx < 0)
		return ;
	if (this->inventory[idx])
		this->inventory[idx] = NULL;
}

void	Character::use(int idx, ICharacter &target)
{
	if (idx >= 4 || idx < 0)
		return ;
	if (this->inventory[idx])
		this->inventory[idx]->use(target);
}


std::string const & Character::getName() const
{
	return this->name;
};


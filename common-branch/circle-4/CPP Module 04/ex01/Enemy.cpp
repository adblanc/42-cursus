/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:37:23 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 16:53:12 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"

Enemy::Enemy(void)
{
	this->type = "Enemie de base";
	this->hp = 10;
};

Enemy::Enemy(int hp, std::string const & type) {
	this->type = type;
	this->hp = hp;
}

Enemy::Enemy(const Enemy &src)
{
	*this = src;
};

Enemy::~Enemy(void)
{

};

Enemy &Enemy::operator= (const Enemy &rhs)
{
	if (this != &rhs)
	{
		this->hp = rhs.hp;
		this->type = rhs.type;
	}
	return (*this);
};

int	Enemy::getHP(void) const {
	return this->hp;
}

std::string const Enemy::getType(void) const {
	return this->type;
}

void	Enemy::takeDamage(int dmg) {
	if (dmg >= 0) {
		if (this->hp - dmg < 0)
			this->hp = 0;
		else
			this->hp -= dmg;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:10:45 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 16:51:24 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP
# define ENEMY_HPP

#include <string>

class Enemy
{
	public:
		Enemy(void);
		Enemy(int hp, std::string const &type);
		Enemy(const Enemy &src);
		virtual ~Enemy(void);

		std::string const getType() const;
		int getHP(void) const;

		virtual void takeDamage(int);

Enemy	&operator=(const Enemy &rhs);

	protected:
		int	hp;
		std::string	type;
};


 #endif

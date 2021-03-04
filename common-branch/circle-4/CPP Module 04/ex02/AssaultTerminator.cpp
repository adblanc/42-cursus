/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssaultTerminator.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:03:20 by adrien            #+#    #+#             */
/*   Updated: 2020/01/08 13:21:20 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AssaultTerminator.hpp"

#include "AssaultTerminator.hpp"

AssaultTerminator::AssaultTerminator(void)
{
    std::cout << "* teleports from space *" << std::endl;
};

AssaultTerminator::AssaultTerminator(const AssaultTerminator &src)
{
    *this = src;
    std::cout << "* teleports from space *" << std::endl;
};

AssaultTerminator::~AssaultTerminator(void)
{
    std::cout << "I’ll be back ...\"" << std::endl;
};

AssaultTerminator &AssaultTerminator::operator= (const AssaultTerminator &rhs)
{
    (void)rhs;
    return (*this);
};


void    AssaultTerminator::battleCry(void) const{
    std::cout << "This code is unclean. Purify it !" << std::endl;
}

void    AssaultTerminator::rangedAttack(void) const {
    std::cout << "* does nothing *" << std::endl;
}

void AssaultTerminator::meleeAttack(void) const {
    std::cout << "* attaque with chainfists *" << std::endl;
}

AssaultTerminator::ISpaceMarine *AssaultTerminator::clone(void) const {
    return (new AssaultTerminator());
}
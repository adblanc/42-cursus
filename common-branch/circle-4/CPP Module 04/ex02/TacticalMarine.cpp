/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TacticalMarine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:01:14 by adrien            #+#    #+#             */
/*   Updated: 2020/01/08 13:34:42 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TacticalMarine.hpp"

TacticalMarine::TacticalMarine(void)
{
    std::cout << "Tactical Marine ready for action!" << std::endl;
};

TacticalMarine::TacticalMarine(const TacticalMarine &src)
{
    *this = src;
     std::cout << "Tactical Marine ready for action!" << std::endl;
};

TacticalMarine::~TacticalMarine(void)
{
    std::cout << "Aaargh ..." << std::endl;
};

TacticalMarine &TacticalMarine::operator= (const TacticalMarine &rhs)
{
    (void)rhs;
    return (*this);
};

void    TacticalMarine::battleCry(void) const{
    std::cout << "For the holy PLOT!" << std::endl;
}

void    TacticalMarine::rangedAttack(void) const {
    std::cout << "* attacks with a bolter *" << std::endl;
}

void TacticalMarine::meleeAttack(void) const {
    std::cout << "* attaque with a chainsword *" << std::endl;
}

TacticalMarine::ISpaceMarine *TacticalMarine::clone(void) const {
    return (new TacticalMarine());
}
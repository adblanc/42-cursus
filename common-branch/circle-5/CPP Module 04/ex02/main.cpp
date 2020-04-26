/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:20:16 by adrien            #+#    #+#             */
/*   Updated: 2020/03/02 20:07:16 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AssaultTerminator.hpp"
#include "TacticalMarine.hpp"
#include "Squad.hpp"

#include <sstream>

int main()
{
    std::stringstream ss;

    ISpaceMarine* bob = new TacticalMarine;
    ISpaceMarine* jim = new AssaultTerminator;
    ISquad* vlc = new Squad;

    ss << vlc->getCount();
    std::cout << "Squad effectif number : " + ss.str() << std::endl;
    ss.str("");

    vlc->push(bob);
    vlc->push(jim);

    ss << vlc->getCount();
    std::cout << "Squad effectif number : " + ss.str() << std::endl;
    ss.str("");

    for (int i = 0; i < vlc->getCount(); ++i)
    {
        ISpaceMarine* cur = vlc->getUnit(i);
        cur->battleCry();
        cur->rangedAttack();
        cur->meleeAttack();
    }

    ISpaceMarine *clone1 = vlc->getUnit(0)->clone();
    ISpaceMarine *clone2 = vlc->getUnit(1)->clone();

    ss << vlc->getCount();
    std::cout << "Squad effectif number : " + ss.str() << std::endl;
    ss.str("");

    std::cout << "On clone.." << std::endl;
    std::cout << "On push les clone" << std::endl;
    vlc->push(clone1);
    vlc->push(clone2);

    ss << vlc->getCount();
    std::cout << "Squad effectif number : " + ss.str() << std::endl;
    ss.str("");

    std::cout << "On essaye de repush les clone" << std::endl;
    vlc->push(clone1);
    vlc->push(clone2);

    ss << vlc->getCount();
    std::cout << "Squad effectif number : " + ss.str() << std::endl;
    ss.str("");

    ISpaceMarine *out = vlc->getUnit(4);
    ISpaceMarine *out_2 = vlc->getUnit(-1);

    if (out == NULL)
        std::cout << "Member out is NULL" << std::endl;
    if (out_2 == NULL)
        std::cout << "Member out_2 is NULL" << std::endl;

    delete vlc;
    return 0;
}

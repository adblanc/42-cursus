/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssaultTerminator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:02:53 by adrien            #+#    #+#             */
/*   Updated: 2020/01/08 13:19:51 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSAULTTERMINATOR_HPP
# define ASSAULTTERMINATOR_HPP

#include <string>
#include <iostream>
#include "ISpaceMarine.hpp"

class AssaultTerminator: public ISpaceMarine
{
    public:
        AssaultTerminator(void);
        AssaultTerminator(const AssaultTerminator &src);
        ~AssaultTerminator();

        AssaultTerminator	&operator=(const AssaultTerminator &rhs);

        virtual ISpaceMarine* clone() const;
        virtual void battleCry() const;
        virtual void rangedAttack() const;
        virtual void meleeAttack() const;

    private:

};

 #endif
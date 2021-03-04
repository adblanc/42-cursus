/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TacticalMarine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:00:43 by adrien            #+#    #+#             */
/*   Updated: 2020/01/08 13:14:31 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TACTICALMARINE_HPP
# define TACTICALMARINE_HPP

#include "ISpaceMarine.hpp"
#include <string>
#include <iostream>

class TacticalMarine: public ISpaceMarine
{
    public:
        TacticalMarine(void);
        TacticalMarine(const TacticalMarine &src);
        ~TacticalMarine(void);

        TacticalMarine	&operator=(const TacticalMarine &rhs);

        virtual ISpaceMarine* clone() const;
        virtual void battleCry() const;
        virtual void rangedAttack() const;
        virtual void meleeAttack() const;
    private:

};


 #endif
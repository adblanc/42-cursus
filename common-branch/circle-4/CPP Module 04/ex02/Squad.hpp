/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Squad.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:29:44 by adrien            #+#    #+#             */
/*   Updated: 2020/03/02 19:49:53 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUAD_HPP
# define SQUAD_HPP

#include "ISquad.hpp"
#include "stdlib.h"

class Squad : public ISquad
{

    public:
        Squad(void);
        Squad(const Squad &src);
        ~Squad(void);

        Squad	&operator=(const Squad &rhs);

        virtual int getCount() const;
        virtual ISpaceMarine* getUnit(int) const;
        virtual int push (ISpaceMarine*);

        struct lst {
            ISpaceMarine *marine;
            lst *next;
        };
        typedef struct lst members;

    private:
        int number;
        members *front;
        members *createMember(ISpaceMarine *);
        void    copyMembers(const Squad &);
        void    deleteMembers(void);
};


 #endif

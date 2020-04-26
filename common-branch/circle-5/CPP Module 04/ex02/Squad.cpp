/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Squad.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:30:20 by adrien            #+#    #+#             */
/*   Updated: 2020/03/02 20:05:20 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Squad.hpp"

Squad::Squad(void)
{
    this->number = 0;
    this->front = NULL;
};

Squad::Squad(const Squad &src)
{
    this->copyMembers(src);
};

Squad::~Squad(void)
{
    this->deleteMembers();
};

Squad &Squad::operator= (const Squad &rhs)
{
    if (this != &rhs)
    {
        this->deleteMembers();
        this->copyMembers(rhs);
    }
    return (*this);
};

int Squad::getCount(void) const {
    return (this->number);
}

ISpaceMarine *Squad::getUnit(int n) const {
    int i;
    members *temp;

    temp = this->front;
    i = 0;
    if (n >= this->number)
        return NULL;
    while (temp != NULL && i <= n) {
        if (i == n)
            return (temp->marine);
        i++;
        temp = temp->next;
    }
    return NULL;
}

int Squad::push(ISpaceMarine *marine) {
    members *temp;

    temp = this->front;
    if (marine == NULL)
        return (this->number);

    if (this->front == NULL) {
        this->front = this->createMember(marine);
        this->number++;
        return (this->number);
    }

    while (temp->next != NULL) {
        if (temp->marine == marine)
            return (this->number);
        temp = temp->next;
    }
        if (temp->marine == marine)
            return (this->number);
    temp->next = this->createMember(marine);
    this->number++;
    return (this->number);
}

void    Squad::copyMembers(const Squad &s) {
    int i;

    i = -1;
    while (++i < s.getCount()) {
        this->push(s.getUnit(i));
    }
}

void    Squad::deleteMembers(void) {
    members *temp;

    while (this->front != NULL) {
        temp = this->front->next;
        delete this->front->marine;
        delete this->front;
        this->front = temp;
    }
}

Squad::members *Squad::createMember(ISpaceMarine *marine) {
    members *newMember;

    newMember = new members();
    newMember->marine = marine;
    newMember->next = NULL;

    return newMember;
}


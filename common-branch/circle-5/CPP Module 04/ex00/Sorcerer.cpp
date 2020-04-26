/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorcerer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 11:35:58 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 17:30:02 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorcerer.hpp"

Sorcerer::Sorcerer(void) {
}

Sorcerer::Sorcerer(const Sorcerer &s) {
	*this = s;
}

Sorcerer::Sorcerer(std::string const & name, std::string const & title) {
	this->name = name;
	this->title = title;
	std::cout << this->name + ", " + this->title + ", is born !" << std::endl;
}

Sorcerer::~Sorcerer() {
	std::cout << this->name + ", " + this->title + ", is dead. Consequences will never be the same !" << std::endl;
}


std::string Sorcerer::getName() const {
	return this->name;
}

std::string Sorcerer::getTitle() const {
	return this->title;
}


void	Sorcerer::polymorph(Victim const &v) const {
	v.getPolymorphed();
}

Sorcerer &Sorcerer::operator=(const Sorcerer &s) {
	if (this != &s) {
		this->name = s.name;
		this->title = s.title;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &out, const Sorcerer &s) {
	out << "I am " + s.getName() + ", " + s.getTitle() + ", and i like ponies!" << std::endl;
	return out;
}



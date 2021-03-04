/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Victim.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:10:38 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 12:38:59 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Victim.hpp"

Victim::Victim(void) {
	std::cout << "Some random victim called " + this->name + " just appeared" << std::endl;
}

Victim::Victim(std::string const &name) {
	this->name = name;
	std::cout << "Some random victim called " + this->name + " just appeared" << std::endl;
}

Victim::~Victim(void) {
	std::cout << "Victim " + this->getName() + " died for no apparent reasons!" << std::endl;
}

Victim::Victim(const Victim &s) {
	*this = s;
}

Victim &Victim::operator=(const Victim &s) {
	if (this != &s) {
		this->name = s.name;
	}
	return (*this);
}

std::string Victim::getName() const {
	return this->name;
}

void	Victim::getPolymorphed(void) const {
	std::cout << this->name + " has been turned into a cute little sheep!" << std::endl;
}

void		Victim::setName(std::string const &name) {
	this->name = name;
}

std::ostream &operator<<(std::ostream &out, const Victim &s) {
	out << "I'm " + s.getName() + " and I like otters!" << std::endl;
	return out;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Peon.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:33:35 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 12:42:58 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Peon.hpp"

Peon::Peon(std::string const &name): Victim(name) {
	this->name = name;
	std::cout << "Zog zog." << std::endl;
}

Peon::Peon(void) {
}

Peon::~Peon(void) {
	std::cout << "Bleuark..." << std::endl;
}

Peon::Peon(const Peon &s) {
	*this = s;
}

Peon &Peon::operator=(const Peon &s) {
	if (this != &s) {
		this->name = s.name;
	}
	return (*this);
}

void	Peon::getPolymorphed(void) const {
	std::cout << this->name + " was juste polymorphed into a pink pony!" << std::endl;
}

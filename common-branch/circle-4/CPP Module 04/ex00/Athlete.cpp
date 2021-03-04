/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Athlete.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:33:35 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 17:39:40 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Athlete.hpp"

Athlete::Athlete(std::string const &name): Victim(name) {
	std::cout << "Run." << std::endl;
}

Athlete::Athlete(void) {
}

Athlete::~Athlete(void) {
	std::cout << "You should have been faster u idiot." << std::endl;
}

Athlete::Athlete(const Athlete &s) {
	*this = s;
}

Athlete &Athlete::operator=(const Athlete &s) {
	if (this != &s) {
		this->name = s.name;
	}
	return (*this);
}

void	Athlete::getPolymorphed(void) const {
	std::cout << this->name + " was juste polymorphed into a pink lion!" << std::endl;
}

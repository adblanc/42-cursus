/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Baker.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:33:35 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 17:39:40 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Baker.hpp"

Baker::Baker(std::string const &name): Victim(name) {
	std::cout << "Bake bake." << std::endl;
}

Baker::Baker(void) {
}

Baker::~Baker(void) {
	std::cout << "Bake.............." << std::endl;
}

Baker::Baker(const Baker &s): Victim(s.name) {

}

Baker &Baker::operator=(const Baker &s) {
	if (this != &s) {
		this->name = s.name;
	}
	return (*this);
}

void	Baker::getPolymorphed(void) const{
	std::cout << this->name + " was juste polymorphed into a pink meduse!" << std::endl;
}

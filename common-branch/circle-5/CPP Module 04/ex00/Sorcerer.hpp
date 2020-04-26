/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorcerer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 11:32:20 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/02 17:30:20 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORCERER_HPP
# define SORCERER_HPP

#include <string>
#include <iostream>
#include "Victim.hpp"

class Sorcerer {

	public:

	Sorcerer(const Sorcerer&);
	Sorcerer(std::string const & name, std::string const & title);
	~Sorcerer();
	Sorcerer &operator=(const Sorcerer&);

	std::string getName(void) const;
	std::string getTitle(void) const;

	void	polymorph(Victim const &) const;

	private:

	Sorcerer(void);

	std::string name;
	std::string title;
};

std::ostream &operator<<(std::ostream &out, const Sorcerer &s);





#endif

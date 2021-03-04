/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Victim.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:08:43 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 12:40:28 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VICTIM_HPP
# define VICTIM_HPP

#include <string>
#include <iostream>

class Victim {

	public:

	Victim(void);
	Victim(std::string const &name);
	Victim(const Victim&);
	~Victim(void);

	Victim &operator=(const Victim &);

	std::string getName(void) const;
	virtual void getPolymorphed() const;

	void	setName(std::string const &name);

	protected:

	std::string name;

};

std::ostream &operator<<(std::ostream &out, const Victim &s);

#endif

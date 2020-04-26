/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Peon.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:31:38 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 12:42:03 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PEON_HPP
# define PEON_HPP

#include <string>
#include <iostream>
#include "Victim.hpp"

class Peon: public Victim {
	public:

	Peon(const Peon &);
	Peon(std::string const & name);
	~Peon(void);

	Peon &operator=(const Peon &);
	virtual void	getPolymorphed(void) const;

	private:

	Peon(void);
};

#endif

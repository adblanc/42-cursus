/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Athlete.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:31:38 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 13:55:56 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATHLETE_HPP
# define ATHLETE_HPP

#include <string>
#include <iostream>
#include "Victim.hpp"

class Athlete: public Victim {
	public:

	Athlete(const Athlete &);
	Athlete(std::string const & name);
	~Athlete(void);

	Athlete &operator=(const Athlete &);
	virtual void	getPolymorphed(void) const;

	private:
	Athlete(void);

};

#endif

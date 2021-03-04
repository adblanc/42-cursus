/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Baker.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:31:38 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 13:55:56 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BAKER_HPP
# define BAKER_HPP

#include <string>
#include <iostream>
#include "Victim.hpp"

class Baker: public Victim {
	public:

	Baker(const Baker &);
	Baker(std::string const & name);
	~Baker(void);

	Baker &operator=(const Baker &);
	virtual void	getPolymorphed(void) const;

	private:

	Baker(void);
};

#endif

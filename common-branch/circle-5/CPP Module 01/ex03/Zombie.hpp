/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:02:44 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 07:10:20 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_H
# define ZOMBIE_H
#include <iostream>

class Zombie
{
	public:

	void		setName(std::string s);
	void		setType(std::string s);
	std::string	getName();
	std::string	getType();
	void		advert();

	private:

	std::string	name;
	std::string	type;
};

#endif

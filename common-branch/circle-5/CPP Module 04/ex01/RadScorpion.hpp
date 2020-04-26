/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RadScorpion.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:54:30 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 16:56:51 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RADSCORPION_HPP
# define RADSCORPION_HPP

#include <string>
#include <iostream>
#include "Enemy.hpp"

class RadScorpion: public Enemy
{
	public:
		RadScorpion(void);
		RadScorpion(const RadScorpion &src);
		~RadScorpion(void);

RadScorpion	&operator=(const RadScorpion &rhs);

	private:

};


 #endif

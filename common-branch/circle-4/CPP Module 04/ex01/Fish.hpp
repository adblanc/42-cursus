/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fish.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:54:30 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 16:56:51 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FISH_HPP
# define FISH_HPP

#include <string>
#include <iostream>
#include "Enemy.hpp"

class Fish: public Enemy
{
	public:
		Fish(void);
		Fish(const Fish &src);
		~Fish(void);

Fish	&operator=(const Fish &rhs);

	private:

};


 #endif

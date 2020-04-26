/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fox.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:54:30 by ablanc            #+#    #+#             */
/*   Updated: 2020/01/07 16:56:51 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOX_HPP
# define FOX_HPP

#include <string>
#include <iostream>
#include "Enemy.hpp"

class Fox: public Enemy
{
	public:
		Fox(void);
		Fox(const Fox &src);
		~Fox(void);

Fox	&operator=(const Fox &rhs);

	private:

};


 #endif

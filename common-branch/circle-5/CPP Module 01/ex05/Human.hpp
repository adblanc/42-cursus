/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:08:38 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 15:16:39 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_H
# define HUMAN_H

#include "Brain.hpp"

class Human
{
	public:

	std::string	identify();
	Brain		getBrain();
	private:
 	Brain brain;
};

#endif

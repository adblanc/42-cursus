/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:08:08 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 15:17:37 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::stringstream	temp;

	temp << this;
	addr =	temp.str();
}

std::string	Brain::identify()
{
	return addr;
}

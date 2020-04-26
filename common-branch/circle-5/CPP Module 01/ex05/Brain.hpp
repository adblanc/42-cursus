/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:08:16 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 15:17:42 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_H
# define BRAIN_H

#include <sstream>
#include <string>

class Brain
{
	public:
	Brain();

	std::string	identify();

	private:
	std::string addr;
};

#endif

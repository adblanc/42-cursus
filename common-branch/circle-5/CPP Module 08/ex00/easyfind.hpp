/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 12:36:42 by adrien            #+#    #+#             */
/*   Updated: 2020/01/16 13:06:30 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
void    easyfind(T const &container, int toFind)
{
    if (std::find(container.begin(), container.end(), toFind) == container.end())
        throw (std::domain_error("Value not found in the container."));
    std::cout << "Value : " << toFind << " found in the container." << std::endl;
}

#endif
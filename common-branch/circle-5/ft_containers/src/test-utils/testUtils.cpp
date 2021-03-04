/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 13:49:41 by adrien            #+#    #+#             */
/*   Updated: 2020/04/06 13:52:11 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testUtils.hpp"

void display(const char *text, const char *color)
{
    std::cout << color << text << COLOR_END << std::endl;
}

void display_success(const char *text)
{
    std::cout << "  ";
    std::cout << COLOR_BLUE << text
              << COLOR_GREEN << " OK"
              << COLOR_END << std::endl;
}
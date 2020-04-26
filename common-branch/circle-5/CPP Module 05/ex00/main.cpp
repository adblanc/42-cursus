/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:46:26 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 08:31:57 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

void    testLowerLimitCreation() {
    try {
        Bureaucrat  adrien("Adrien", 150);
        std::cout << adrien;

        std::cout << "Let's try to create a 151 grade bureaucrat" << std::endl;
        Bureaucrat("Adrien but too lowkey", 151);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

void    testUpperLimitCreation() {
    try {
        Bureaucrat  adrien("Adrien", 1);
        std::cout << adrien;

        std::cout << "Let's try to create a 0 grade bureaucrat" << std::endl;
        Bureaucrat("Adrien but too high", 0);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

void    testLowerLimitDecrement() {
    try {
        Bureaucrat  adrien("Adrien", 150);
        std::cout << adrien;

        std::cout << "Let's try to decrement a 150 grade bureaucrat" << std::endl;
        adrien.decrementGrade();
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

void    testUpperLimitIncrement() {
    try {
        Bureaucrat  adrien("Adrien", 1);
        std::cout << adrien;

        std::cout << "Let's try to increment a 1 grade bureaucrat" << std::endl;
        adrien.incrementGrade();
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    testLowerLimitCreation();
    std::cout << "------------------------------" << std::endl;
    testUpperLimitCreation();
    std::cout << "------------------------------" << std::endl;
    testLowerLimitDecrement();
    std::cout << "------------------------------" << std::endl;
    testUpperLimitIncrement();
    return (0);
}

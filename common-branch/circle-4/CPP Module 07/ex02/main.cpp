/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:17:54 by adrien            #+#    #+#             */
/*   Updated: 2020/01/15 12:23:32 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Array.hpp"

int main()
{
    try {

        Array<int> empty;

         std::cout << "--- Empty Array---" << std::endl;
         std::cout << "Size : " << empty.size() << std::endl;
        

        Array<int> intArray(5);

        intArray[2] = 5;
        intArray[4] = 4;

        std::cout << "--- Array ---" << std::endl;
        intArray.print();

        Array<int> copy = intArray;

        copy[0] = 7;
        copy[2] = 3;

        std::cout << "--- Copy modified: ---" << std::endl;
        copy.print();

        std::cout << "--- Array ---" << std::endl;
        intArray.print();

        intArray[5] = 2;

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return (0);
}
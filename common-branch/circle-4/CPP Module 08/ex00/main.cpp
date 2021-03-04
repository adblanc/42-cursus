/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:00:19 by adrien            #+#    #+#             */
/*   Updated: 2020/01/16 13:11:20 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>
#include <list>
#include <array>
#include <iostream>

int main()
{
    std::cout << "--- Vector ---" << std::endl << std::endl;
    try {
        std::vector<int> test1;

        for (int i = 0; i < 5 ; i++)
            test1.push_back(i);

        easyfind(test1, 4);
        easyfind(test1, 5);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl << "--- List ---" << std::endl << std::endl;
    try {
        std::list<int> list1;

        for (int i = 0; i < 10 ; i++)
            list1.push_front(i);

        easyfind(list1, 1);
        easyfind(list1, 11);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl << "--- Array ---" << std::endl << std::endl;
    try {
        std::array<int, 5> array1 = {1, 2, 3, 4, 5}; 

        easyfind(array1, 1);
        easyfind(array1, 11);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return (0);
}
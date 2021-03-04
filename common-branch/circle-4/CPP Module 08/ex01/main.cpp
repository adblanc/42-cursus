/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:20:55 by adrien            #+#    #+#             */
/*   Updated: 2020/03/11 11:03:15 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

int main()
{

    std::cout << std::endl
              << "--- Span + span limits ---" << std::endl;

    try
    {
        Span sp = Span(5);

        sp.addNumber(5);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << sp.shortestSpan() << std::endl;

        std::cout << sp.longestSpan() << std::endl;

        sp.addNumber(99);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl
              << "--- Span with only 1 or 0 numbers ---" << std::endl;

    try
    {
        Span sp = Span(5);

        sp.addNumber(1);

        std::cout << sp.shortestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        Span sp = Span(5);

        std::cout << sp.longestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        Span sp = Span(15000);
        for (int i = 0; i < 15000; i++)
            sp.addNumber(i);

        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::vector<int> vect;
        for (int i = 0; i < 3; i++)
            vect.push_back(i);

        Span sp = Span(3);

        sp.addNumber(vect.begin(), vect.end());

        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return (0);
}

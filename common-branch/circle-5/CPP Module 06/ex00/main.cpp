/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:12:07 by adrien            #+#    #+#             */
/*   Updated: 2020/03/09 14:45:23 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConvertScalar.hpp"
#include "main.hpp"

int main(int ac, char **av)
{
    std::string input;

    if (ac == 2)
    {
        try
        {
            input = av[1];
            ConvertScalar conv(input);

            conv.displayChar();
            conv.displayInt();
            conv.displayFloat();
            conv.displayDouble();
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    return (0);
}

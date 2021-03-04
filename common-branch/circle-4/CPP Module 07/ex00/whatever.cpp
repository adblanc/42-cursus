/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 10:11:13 by adrien            #+#    #+#             */
/*   Updated: 2020/03/09 17:26:29 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <typename T>
T min(T const &a, T const &b)
{
    return (a < b ? a : b);
}

template <typename T>
T max(T const &a, T const &b)
{
    return (a > b ? a : b);
}

template <typename T>
void swap(T &a, T &b)
{
    T temp(a);

    a = b;
    b = temp;
}

int main()
{
    std::cout << "--- min && max ---" << std::endl
              << std::endl;

    std::cout << "int || min(5, 10) : ";
    std::cout << min(static_cast<int>(5), static_cast<int>(10)) << std::endl;

    std::cout << "int || min(10, 5) : ";
    std::cout << min(static_cast<int>(10), static_cast<int>(5)) << std::endl;

    std::cout << "int || max(5, 10) : ";
    std::cout << max(static_cast<int>(5), static_cast<int>(10)) << std::endl;

    std::cout << "int || max(10, 5) : ";
    std::cout << max(static_cast<int>(10), static_cast<int>(5)) << std::endl;

    std::cout << std::endl;

    std::cout << "float || min(5.5, 10) : ";
    std::cout << min(static_cast<float>(5.5), static_cast<float>(10)) << std::endl;

    std::cout << "float || min(10, 5.5) : ";
    std::cout << min(static_cast<float>(10), static_cast<float>(5.5)) << std::endl;

    std::cout << "float || max(5.5, 10) : ";
    std::cout << max(static_cast<float>(5.5), static_cast<float>(10)) << std::endl;

    std::cout << "float || max(10, 5.5) : ";
    std::cout << max(static_cast<float>(10), static_cast<float>(5.5)) << std::endl;

    std::cout << std::endl
              << std::endl;

    std::cout << "--- swap ---" << std::endl
              << std::endl;

    int a = 5;
    int b = 10;

    float fa = 5.5;
    float fb = 10;

    std::string s1 = "chaine1";
    std::string s2 = "chaine2";

    std::cout << "int //" << std::endl;
    std::cout << "a: " << a << " b: " << b << std::endl;
    std::cout << "swap" << std::endl;
    swap(a, b);
    std::cout << "a: " << a << " b: " << b << std::endl;

    std::cout << "float //" << std::endl;
    std::cout << "fa: " << fa << " fb: " << fb << std::endl;
    std::cout << "swap" << std::endl;
    swap(fa, fb);
    std::cout << "fa: " << fa << " fb: " << fb << std::endl;

    std::cout << "string //" << std::endl;
    std::cout << "s1: " << s1 << " s2: " << s2 << std::endl;
    std::cout << "swap" << std::endl;
    swap(s1, s2);
    std::cout << "s1: " << s1 << " s2: " << s2 << std::endl;

    return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 10:30:30 by adrien            #+#    #+#             */
/*   Updated: 2020/03/09 17:28:49 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <typename T>
void iter(T *array, unsigned int length, void fn(T const &))
{
    unsigned int i;

    i = 0;
    while (array && i < length)
        fn(array[i++]);
}

template <typename T>
void display(T const &a)
{
    std::cout << a << std::endl;
}

int main()
{
    int array1[] = {1, 2, 3, 4, 5};
    float array2[] = {1.5, 2.5, 3.5, 4.5, 5.5};
    std::string array3[] = {"salut", "ok", "merci"};

    iter(array1, 5, display);
    iter(array2, 5, display);
    iter(array3, 3, display);

    return (0);
}

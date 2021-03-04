/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:36:47 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 13:39:04 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test-utils/testUtils.hpp"

int main()
{

    test_iterators();
    test_pair();
    test_list();
    test_vector();
    test_red_black_tree();
    test_map();
    test_stack();
    test_queue();

    test_multimap();
    test_set();
    test_multiset();

    return (0);
}

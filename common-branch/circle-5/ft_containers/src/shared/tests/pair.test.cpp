/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:40:53 by adrien            #+#    #+#             */
/*   Updated: 2020/04/14 19:59:22 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pair.hpp"
#include "../../test-utils/testUtils.hpp"
#include <string>

template <class T1, class T2>
void test_pair_constructor()
{
    ft::Pair<T1, T2> a;
    ft::Pair<T1, T2> b;

    assert(a.first == T1());
    assert(a.second == T2());

    assert(a == b);
}

void test_pair_practical()
{
    ft::Pair<int, float> a(5, 5.5);
    ft::Pair<int, float> b(10, 10.5);

    assert(a.first == 5);
    assert(a.second == 5.5);

    assert(b.first == 10);
    assert(b.second == 10.5);

    assert(a < b);
    assert(a <= b);
    assert(b > a);
    assert(b >= a);
    assert(b != a);

    a = b;

    assert(a == b);
    assert(a.first == 10);
    assert(a.second == 10.5);
}

void test_pair()
{
    display("          === pair ===", COLOR_CYAN);
    test_pair_constructor<int, int>();
    test_pair_constructor<float, int>();
    test_pair_constructor<char, std::string>();
    test_pair_constructor<char *, std::string>();
    test_pair_constructor<char *, char *>();
    test_pair_constructor<double, double>();

    test_pair_practical();

    display_success("Pair<T1, T2>");
}
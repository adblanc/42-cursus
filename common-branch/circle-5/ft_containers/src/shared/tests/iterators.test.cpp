/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.test.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:30:43 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/24 13:46:53 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test-utils/testUtils.hpp"

template <class T>
static void test_it(const T &cont)
{
	typename T::const_iterator it_var;

	for (typename T::const_iterator it(cont.begin()); it != cont.end(); ++it)
	{
		it_var = it;
	}
}

template <class T>
static void test_rev_it(const T &cont)
{
	typename T::const_reverse_iterator rit_var;

	for (typename T::const_reverse_iterator it(cont.rbegin()); it != cont.rend(); ++it)
	{
		rit_var = it;
	}
}

void test_iterators()
{
	display("          === Iterators ===", COLOR_CYAN);

	ft::list<int> list;
	ft::vector<int> vec;
	ft::map<int, int> map;

	list.push_back(5);
	list.push_back(6);

	vec.push_back(5);
	vec.push_back(6);

	map.insert(ft::Pair<int, int>(5, 5));
	map.insert(ft::Pair<int, int>(6, 6));

	test_it(list);
	test_it(vec);
	test_it(map);

	test_rev_it(list);
	test_rev_it(vec);
	test_rev_it(map);

	display_success("Iterators");
}

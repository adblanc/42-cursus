/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testUtils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 13:49:19 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:09:26 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <queue>

#include "../list/List.hpp"
#include "../vector/Vector.hpp"
#include "../map/Map.hpp"

#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_END "\033[0m"
#define UNDERLINE "\033[4m"

// Helpers
void display(const char *text, const char *color);
void display_success(const char *text);

void test_list();
void test_vector();
void test_pair();
void test_iterators();
void test_red_black_tree();
void test_map();
void test_stack();
void test_queue();

void test_multimap();
void test_set();
void test_multiset();

#endif

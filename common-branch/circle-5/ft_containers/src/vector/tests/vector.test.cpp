/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 13:36:32 by adrien            #+#    #+#             */
/*   Updated: 2020/04/14 19:21:09 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test-utils/testUtils.hpp"

size_t DEFAULT_LENGTH = 50;

// Constructors

template <typename T>
static void test_default_constructor()
{
    ft::vector<T> vec;

    assert(vec.empty() == true);
    assert(vec.size() == 0);
}

static void default_constructor()
{
    test_default_constructor<int>();
    test_default_constructor<float>();
    test_default_constructor<char>();
    test_default_constructor<char *>();
    test_default_constructor<std::string>();

    display_success("default constructor");
}

template <typename T>
static void test_fill_constructor()
{
    size_t length = 50;
    ft::vector<T> vec(length);

    assert(vec.empty() == false);
    assert(vec.size() == length);
    for (size_t i = 0; i < length; i++)
        assert(vec[i] == T());
}

static void fill_constructor()
{
    test_fill_constructor<int>();
    test_fill_constructor<float>();
    test_fill_constructor<char>();
    test_fill_constructor<char *>();
    test_fill_constructor<std::string>();

    display_success("fill constructor");
}

template <typename T>
static void test_range_constructor()
{
    ft::vector<T> vec_empty;
    ft::vector<T> vec(DEFAULT_LENGTH);

    ft::vector<T> vec_range(vec.begin(), vec.end());
    ft::vector<T> vec_range_empty(vec_empty.begin(), vec_empty.end());

    vec.push_back(T());
    vec_empty.push_back(T());

    assert(vec_range.size() == DEFAULT_LENGTH);
    assert(vec_range.capacity() == DEFAULT_LENGTH);

    assert(vec_range_empty.empty());
    assert(vec_range_empty.capacity() == 0);
}

static void range_constructor()
{
    test_range_constructor<int>();
    test_range_constructor<float>();
    test_range_constructor<char>();
    test_range_constructor<char *>();
    test_range_constructor<std::string>();

    display_success("range constructor");
}

template <typename T>
static void test_copy_constructor()
{
    ft::vector<T> vec_empty;
    ft::vector<T> vec(DEFAULT_LENGTH);

    ft::vector<T> vec_copy(vec);
    ft::vector<T> vec_copy_empty(vec_empty);

    vec.push_back(T());
    vec_empty.push_back(T());

    assert(vec_copy.size() == DEFAULT_LENGTH);
    assert(vec_copy.capacity() == DEFAULT_LENGTH);

    assert(vec_copy_empty.empty());
    assert(vec_copy_empty.capacity() == 0);
}

static void copy_constructor()
{
    test_copy_constructor<int>();
    test_copy_constructor<float>();
    test_copy_constructor<char>();
    test_copy_constructor<char *>();
    test_copy_constructor<std::string>();

    display_success("copy constructor");
}

template <typename T>
static void test_assignement_operator()
{
    ft::vector<T> vec_empty;
    ft::vector<T> vec(DEFAULT_LENGTH);

    ft::vector<T> vec_copy = vec;
    ft::vector<T> vec_copy_empty = vec_empty;

    vec.push_back(T());
    vec_empty.push_back(T());

    assert(vec_copy.size() == DEFAULT_LENGTH);
    assert(vec_copy.capacity() == DEFAULT_LENGTH);

    assert(vec_copy_empty.empty());
    assert(vec_copy_empty.capacity() == 0);

    vec_copy_empty = vec_copy;
    assert(vec_copy_empty.size() == DEFAULT_LENGTH);
    assert(vec_copy_empty.capacity() == vec_copy.capacity());
}

static void assignement_operator()
{
    test_assignement_operator<int>();
    test_assignement_operator<float>();
    test_assignement_operator<char>();
    test_assignement_operator<char *>();
    test_assignement_operator<std::string>();

    display_success("assignement_operator");
}

// Iterators

static void test_begin_end_practical()
{
    ft::vector<int> vec(DEFAULT_LENGTH, 5);

    vec.push_back(6);
    vec.insert(vec.begin(), 4);

    assert(*(vec.begin()) == 4);
    assert(*(vec.end() - 1) == 6);
}

template <typename T>
static void test_begin_end()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    assert(vec.end() - vec.end() == 0);
    assert(vec.begin() - vec.begin() == 0);
    assert(vec.begin() + 5 - vec.begin() == 5);
    assert(vec.end() - vec.begin() == (int)DEFAULT_LENGTH);
}

static void begin_end()
{
    test_begin_end_practical();
    test_begin_end<int>();
    test_begin_end<float>();
    test_begin_end<char>();
    test_begin_end<char *>();
    test_begin_end<std::string>();

    display_success("begin && end");
}

template <typename T>
static void test_rbegin_rend()
{
    std::vector<T> vec(DEFAULT_LENGTH);
    ft::vector<T> ft_vec(DEFAULT_LENGTH);

    assert(*(vec.rend() - 1) == vec.front());
    assert(*(vec.rbegin()) == vec.back());

    assert(*(ft_vec.rend() - 1) == ft_vec.front());
    assert(*(ft_vec.rbegin()) == ft_vec.back());

    assert(vec.rbegin() - vec.rbegin() == 0);
    assert(vec.rend() + 5 == vec.rend() + 5);
    assert(vec.rend() - vec.rbegin() == (int)DEFAULT_LENGTH);

    assert(ft_vec.rbegin() - ft_vec.rbegin() == 0);
    assert(ft_vec.rend() + 5 == ft_vec.rend() + 5);
    assert(ft_vec.rend() - ft_vec.rbegin() == (int)DEFAULT_LENGTH);
}

static void test_rbegin_rend_practical()
{
    std::vector<int> vec(DEFAULT_LENGTH, 1);

    vec.push_back(2);
    vec.push_back(3);
    vec.insert(vec.begin(), 0);

    assert(*(vec.rbegin()) == 3 && *(vec.rbegin()) == vec.back());
    assert(*(vec.rbegin() + 1) == 2);
    assert(*(vec.rend() - 1) == 0 && *(vec.rend() - 1) == vec.front());
    assert(*(vec.rend() - 2) == 1);

    vec.pop_back();
    assert(*(vec.rbegin()) == 2 && *(vec.rbegin()) == vec.back());

    ft::vector<int> ft_vec(DEFAULT_LENGTH, 1);

    ft_vec.push_back(2);
    ft_vec.push_back(3);
    ft_vec.insert(ft_vec.begin(), 0);

    assert(*(ft_vec.rbegin()) == 3 && *(ft_vec.rbegin()) == ft_vec.back());
    assert(*(ft_vec.rbegin() + 1) == 2);
    assert(*(ft_vec.rend() - 1) == 0 && *(ft_vec.rend() - 1) == ft_vec.front());
    assert(*(ft_vec.rend() - 2) == 1);

    ft_vec.pop_back();
    assert(*(ft_vec.rbegin()) == 2 && *(ft_vec.rbegin()) == ft_vec.back());
}

static void rbegin_rend()
{
    test_rbegin_rend_practical();
    test_rbegin_rend<int>();
    test_rbegin_rend<float>();
    test_rbegin_rend<char>();
    test_rbegin_rend<char *>();
    test_rbegin_rend<std::string>();

    display_success("rbegin && rend");
}

// Capacity

template <typename T>
static void test_size()
{
    ft::vector<T> vec_empty;
    ft::vector<T> vec(DEFAULT_LENGTH);

    assert(!vec_empty.size() && vec_empty.empty());

    assert(vec.size() == DEFAULT_LENGTH);

    vec.pop_back();
    assert(vec.size() == DEFAULT_LENGTH - 1);
}

static void size()
{
    test_size<int>();
    test_size<float>();
    test_size<char>();
    test_size<char *>();
    test_size<std::string>();

    display_success("size");
}

static void max_size()
{
    display_success("max_size");
}

template <typename T>
static void test_resize_greater()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    vec.resize(DEFAULT_LENGTH * 2);

    assert(vec.size() == DEFAULT_LENGTH * 2);

    for (size_t i = 0; i < vec.size(); i++)
        assert(vec[i] == T());
}

template <typename T>
static void test_resize_smaller()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    vec.resize(DEFAULT_LENGTH / 2);

    assert(vec.size() == DEFAULT_LENGTH / 2);

    for (size_t i = 0; i < vec.size(); i++)
        assert(vec[i] == T());
}

template <typename T>
static void test_resize()
{
    test_resize_greater<T>();
    test_resize_smaller<T>();
}

static void resize()
{
    test_resize<int>();
    test_resize<float>();
    test_resize<char>();
    test_resize<char *>();
    test_resize<std::string>();

    display_success("resize");
}

template <typename T>
static void test_capacity()
{
    ft::vector<T> vec;

    for (size_t i = 0; i < 1; i++)
    {
        vec.push_back(T());
        assert(vec.capacity() >= vec.size());
    }

    assert(vec.size() == 1);

    vec.insert(vec.begin(), DEFAULT_LENGTH, T());
    assert(vec.capacity() >= vec.size());
}

static void capacity()
{
    test_capacity<int>();
    test_capacity<float>();
    test_capacity<char>();
    test_capacity<char *>();
    test_capacity<std::string>();

    display_success("capacity");
}

template <typename T>
static void test_empty()
{
    ft::vector<T> vec(DEFAULT_LENGTH);
    ft::vector<T> vec_empty;

    assert(!vec.empty());
    assert(vec_empty.empty() && !vec_empty.size());

    for (size_t i = 0; i < DEFAULT_LENGTH; i++)
        vec.pop_back();
    assert(vec.empty());
    vec.push_back(T());
    assert(!vec.empty());
}

static void empty()
{
    test_empty<int>();
    test_empty<float>();
    test_empty<char>();
    test_empty<char *>();
    test_empty<std::string>();

    display_success("empty");
}

template <typename T>
static void test_at()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    try
    {
        vec.at(-1) = T();
        assert(0);
    }
    catch (std::out_of_range &e)
    {
        assert(1);
    }

    try
    {
        vec.at(DEFAULT_LENGTH) = T();
        assert(0);
    }
    catch (std::out_of_range &e)
    {
        assert(1);
    }

    try
    {
        vec.at(DEFAULT_LENGTH + 1) = T();
        assert(0);
    }
    catch (std::out_of_range &e)
    {
        assert(1);
    }
}

static void at()
{
    test_at<int>();
    test_at<float>();
    test_at<char>();
    test_at<char *>();
    test_at<std::string>();

    display_success("at");
}

static void test_front_back_practical()
{
    ft::vector<int> vec(DEFAULT_LENGTH);

    vec[0] = 1;
    vec[DEFAULT_LENGTH - 1] = 2;

    assert(vec.front() == 1);
    assert(vec.back() == 2);
}

template <typename T>
static void test_front_back()
{
    ft::vector<T> vec(DEFAULT_LENGTH);
    const ft::vector<T> vec_const(DEFAULT_LENGTH);

    assert(vec.front() == T());
    assert(vec.back() == T());
    assert(vec_const.front() == T());
    assert(vec_const.back() == T());
}

static void front_back()
{
    test_front_back_practical();
    test_front_back<int>();
    test_front_back<float>();
    test_front_back<char>();
    test_front_back<char *>();
    test_front_back<std::string>();

    display_success("front && back");
}

static void test_access_operator_practical()
{
    ft::vector<int> vec(DEFAULT_LENGTH);

    vec[0] = 1;
    vec[DEFAULT_LENGTH - 1] = 2;

    assert(*(vec.begin()) == 1);
    assert(*(vec.end() - 1) == 2);
}

template <typename T>
static void test_access_operator()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    vec[0] = T();
    vec[DEFAULT_LENGTH - 1] = T();

    assert(*(vec.begin()) == T());
    assert(*(vec.end() - 1) == T());
}

static void access_operator()
{
    test_access_operator_practical();
    test_access_operator<int>();
    test_access_operator<float>();
    test_access_operator<char>();
    test_access_operator<char *>();
    test_access_operator<std::string>();

    display_success("access operator");
}

template <typename T>
static void reserve_no_realloc_smaller()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    assert(vec.size() == DEFAULT_LENGTH);
    assert(vec.capacity() == DEFAULT_LENGTH);

    vec.reserve(DEFAULT_LENGTH - 1);

    assert(vec.capacity() == DEFAULT_LENGTH);
    assert(vec.size() == DEFAULT_LENGTH);

    for (size_t i = 0; i < vec.size(); i++)
        assert(vec[i] == T());
}

template <typename T>
static void reserve_realloc_if_greater()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    assert(vec.size() == DEFAULT_LENGTH);
    assert(vec.capacity() == DEFAULT_LENGTH);

    vec.reserve(DEFAULT_LENGTH * 2);

    assert(vec.capacity() == DEFAULT_LENGTH * 2);
    assert(vec.size() == DEFAULT_LENGTH);

    for (size_t i = 0; i < vec.size(); i++)
        assert(vec[i] == T());
}

template <typename T>
static void reserve_throw_error_when_exceed_max_size()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    assert(vec.size() == DEFAULT_LENGTH);
    assert(vec.capacity() == DEFAULT_LENGTH);

    try
    {
        vec.reserve(vec.max_size() + 1);
        assert(0);
    }
    catch (std::length_error &e)
    {
        assert(1);
        assert(vec.capacity() == DEFAULT_LENGTH);
        assert(vec.size() == DEFAULT_LENGTH);

        for (size_t i = 0; i < vec.size(); i++)
            assert(vec[i] == T());
    }
}

template <typename T>
static void test_reserve()
{
    reserve_no_realloc_smaller<T>();
    reserve_realloc_if_greater<T>();
    reserve_throw_error_when_exceed_max_size<T>();
}

static void reserve()
{
    test_reserve<int>();
    test_reserve<float>();
    test_reserve<char>();
    test_reserve<char *>();
    test_reserve<std::string>();

    display_success("reserve");
}

// Modifiers

template <typename T>
static void test_assign_range()
{
    ft::vector<T> vec_empty;
    ft::vector<T> vec(DEFAULT_LENGTH);
    ft::vector<T> vec_half(DEFAULT_LENGTH / 2);

    vec_empty.assign(vec.begin(), vec.end());

    assert(vec_empty.size() == DEFAULT_LENGTH);

    vec_half.assign(vec.begin(), vec.end());

    assert(vec_half.size() == DEFAULT_LENGTH);
}

template <typename T>
static void test_assign_fill()
{
    ft::vector<T> vec_empty;
    ft::vector<T> vec(DEFAULT_LENGTH);
    ft::vector<T> vec_half(DEFAULT_LENGTH / 2);

    vec_empty.assign(DEFAULT_LENGTH, T());

    assert(vec_empty.size() == DEFAULT_LENGTH);

    vec_half.assign(DEFAULT_LENGTH, T());

    assert(vec_half.size() == DEFAULT_LENGTH);
}

template <typename T>
static void test_assign()
{
    test_assign_fill<T>();
    test_assign_range<T>();
}

static void test_assign_practical()
{
    ft::vector<int> vec;
    ft::vector<int> vec_filled(DEFAULT_LENGTH * 2, 6);
    ft::vector<int> vec_empty;

    vec.assign(DEFAULT_LENGTH, 5);

    assert(vec.size() == DEFAULT_LENGTH);
    for (size_t i = 0; i < vec.size(); i++)
        assert(vec[i] == 5);

    vec.assign(vec_filled.begin(), vec_filled.end());

    assert(vec.size() == DEFAULT_LENGTH * 2);
    for (size_t i = 0; i < vec.size(); i++)
        assert(vec[i] == 6);

    vec.assign(vec_empty.begin(), vec_empty.end());
    assert(vec.empty());
}

static void assign()
{
    test_assign_practical();
    test_assign<int>();
    test_assign<float>();
    test_assign<char>();
    test_assign<char *>();
    test_assign<std::string>();

    display_success("assign");
}

template <typename T>
static void test_push_back()
{
    ft::vector<T> vec;

    while (vec.size() < DEFAULT_LENGTH)
        vec.push_back(T());

    assert(vec.size() == DEFAULT_LENGTH);

    for (size_t i = 0; i < vec.size(); i++)
        assert(vec[i] == T());
}

static void test_push_back_practical()
{
    ft::vector<int> vec;
    const ft::vector<int> vec_const(DEFAULT_LENGTH, 5);

    for (int i = 0; i < (int)DEFAULT_LENGTH; i++)
        vec.push_back(i);
    assert(vec.size() == DEFAULT_LENGTH);
    assert(*(vec.begin()) == 0);
    assert(*(vec.end() - 1) == 49);

    assert(vec_const.size() == DEFAULT_LENGTH);
    assert(*(vec_const.begin()) == 5);
    assert(*(vec_const.end() - 1) == 5);
}

static void push_back()
{
    test_push_back_practical();
    test_push_back<int>();
    test_push_back<float>();
    test_push_back<char>();
    test_push_back<char *>();
    test_push_back<std::string>();

    display_success("push_back");
}

static void test_pop_back_practical()
{
    ft::vector<int> vec(DEFAULT_LENGTH, 5);

    vec.push_back(6);
    vec.push_back(7);
    vec.pop_back();
    assert(vec.size() == DEFAULT_LENGTH + 1);
    assert(vec.back() == 6);
}

template <typename T>
static void test_pop_back()
{
    ft::vector<T> vec(DEFAULT_LENGTH);
    ft::vector<T> vec_2(DEFAULT_LENGTH);

    while (!vec.empty())
        vec.pop_back();

    for (size_t i = 0; i < vec_2.size(); i++)
    {
        assert(vec_2.size() == DEFAULT_LENGTH - i);
        vec_2.pop_back();
    }
}

static void pop_back()
{
    test_pop_back_practical();
    test_pop_back<int>();
    test_pop_back<float>();
    test_pop_back<char>();
    test_pop_back<char *>();
    test_pop_back<std::string>();

    display_success("pop_back");
}

template <typename T>
static void test_insert_range()
{
    ft::vector<T> vec(DEFAULT_LENGTH);
    ft::vector<T> vec_empty;
    ft::vector<T> vec_2(DEFAULT_LENGTH);

    vec.insert(vec.begin(), vec_2.begin(), vec_2.end());

    assert(vec.size() == DEFAULT_LENGTH * 2);

    vec.insert(vec.begin(), vec_empty.begin(), vec_empty.end());

    assert(vec.size() == DEFAULT_LENGTH * 2);

    vec.insert(vec.begin() + 5, vec_2.begin(), vec_2.end());

    assert(vec.size() == DEFAULT_LENGTH * 3);
}

template <typename T>
static void test_insert_single()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    typename ft::vector<T>::iterator it = vec.begin();

    vec.insert(vec.begin(), T());
    assert(it != vec.begin());
    assert(vec.size() == DEFAULT_LENGTH + 1);
    vec.insert(vec.end(), T());
    assert(vec.size() == DEFAULT_LENGTH + 2);

    vec.insert(vec.end() - 2, T());
    assert(vec.size() == DEFAULT_LENGTH + 3);

    vec.insert(vec.begin() + 2, T());
    assert(vec.size() == DEFAULT_LENGTH + 4);
}

template <typename T>
static void test_insert_fill()
{
    ft::vector<T> vec(DEFAULT_LENGTH);

    vec.insert(vec.begin(), DEFAULT_LENGTH, T());
    assert(vec.size() == DEFAULT_LENGTH * 2);

    vec.insert(vec.end(), DEFAULT_LENGTH, T());
    assert(vec.size() == DEFAULT_LENGTH * 3);

    vec.insert(vec.begin() + 5, DEFAULT_LENGTH, T());
    assert(vec.size() == DEFAULT_LENGTH * 4);
}

template <typename T>
static void test_insert()
{
    test_insert_single<T>();
    test_insert_fill<T>();
    test_insert_range<T>();
}

static void test_insert_practical()
{
    ft::vector<int> vec(DEFAULT_LENGTH, 5);
    ft::vector<int> vec_2(DEFAULT_LENGTH, 2);

    vec.insert(vec.begin(), 0);
    assert(vec.front() == 0);
    assert(vec.size() == DEFAULT_LENGTH + 1);

    vec.insert(vec.end(), 1);
    assert(vec.back() == 1);
    assert(vec.size() == DEFAULT_LENGTH + 2);

    vec.insert(vec.begin() + 5, DEFAULT_LENGTH, 6);
    assert(*(vec.begin() + 5) == 6 && *(vec.begin() + 4) == 5);
    assert(vec.size() == DEFAULT_LENGTH * 2 + 2);

    vec.insert(vec.end(), vec_2.begin(), vec_2.end());
    assert(vec.size() == DEFAULT_LENGTH * 3 + 2);
    assert(vec.back() == 2);
}

static void insert()
{
    test_insert_practical();
    test_insert<int>();
    test_insert<float>();
    test_insert<char>();
    test_insert<char *>();
    test_insert<std::string>();

    display_success("insert");
}

template <typename T>
static void test_erase()
{
    ft::vector<T> vec(DEFAULT_LENGTH);
    std::vector<T> std_vec(DEFAULT_LENGTH);

    vec.erase(vec.begin(), vec.end());
    std_vec.erase(std_vec.begin(), std_vec.end());

    assert(vec.empty());
    assert(std_vec.empty());

    ft::vector<T> vec_2(DEFAULT_LENGTH);
    std::vector<T> std_vec_2(DEFAULT_LENGTH);

    vec_2.erase(vec_2.begin() + 5, vec_2.begin() + 10);
    std_vec_2.erase(std_vec_2.begin() + 5, std_vec_2.begin() + 10);
    assert(vec_2.size() == DEFAULT_LENGTH - 5);
    assert(std_vec_2.size() == DEFAULT_LENGTH - 5);

    for (size_t i = 0; i < vec_2.size(); i++)
    {
        assert(vec_2[i] == T());
        assert(std_vec_2[i] == T());
    }

    int i = 0;
    typename ft::vector<T>::iterator it = vec_2.begin();
    while (!vec_2.empty())
    {
        i++;
        it = vec_2.erase(it);
        assert(vec_2.size() == DEFAULT_LENGTH - 5 - i);
    }
    i = 0;
    typename std::vector<T>::iterator std_it = std_vec_2.begin();
    while (!std_vec_2.empty())
    {
        i++;
        std_it = std_vec_2.erase(std_it);
        assert(std_vec_2.size() == DEFAULT_LENGTH - 5 - i);
    }
}

static void erase()
{
    test_erase<int>();
    test_erase<float>();
    test_erase<char>();
    test_erase<char *>();
    test_erase<std::string>();

    display_success("erase");
}

static void test_swap_practical()
{
    ft::vector<int> vec_1(DEFAULT_LENGTH * 2, 1);
    ft::vector<int> vec_2(DEFAULT_LENGTH, 2);

    size_t vec_1_cap = vec_1.capacity();
    size_t vec_1_size = vec_1.size();
    size_t vec_2_cap = vec_2.capacity();
    size_t vec_2_size = vec_2.size();

    vec_1.swap(vec_2);

    assert(vec_1.size() == vec_2_size);
    assert(vec_1.capacity() == vec_2_cap);
    assert(vec_2.size() == vec_1_size);
    assert(vec_2.capacity() == vec_1_cap);

    for (size_t i = 0; i < vec_1.size(); i++)
        assert(vec_1[i] == 2);
    for (size_t i = 0; i < vec_2.size(); i++)
        assert(vec_2[i] == 1);
}

template <typename T>
static void test_swap()
{
    size_t vec_1_size = DEFAULT_LENGTH;
    size_t vec_2_size = DEFAULT_LENGTH * 2;
    ft::vector<T> vec_1(vec_1_size);
    ft::vector<T> vec_2(vec_2_size);

    typename ft::vector<T>::iterator begin_vec_1 = vec_1.begin();
    typename ft::vector<T>::iterator end_vec_1 = vec_1.end();
    typename ft::vector<T>::iterator begin_vec_2 = vec_2.begin();
    typename ft::vector<T>::iterator end_vec_2 = vec_2.end();

    vec_1.swap(vec_2);

    assert(vec_1.size() == vec_2_size);
    assert(vec_2.size() == vec_1_size);
    assert(vec_1.capacity() == vec_2_size);
    assert(vec_2.capacity() == vec_1_size);

    assert(vec_1.begin() == begin_vec_2);
    assert(vec_1.end() == end_vec_2);
    assert(vec_2.begin() == begin_vec_1);
    assert(vec_2.end() == end_vec_1);

    vec_1.push_back(T());

    assert(vec_1.size() == vec_2_size + 1);
    assert(vec_2.size() == vec_1_size);

    vec_2.clear();
    assert(vec_2.empty());
    assert(vec_1.size() == vec_2_size + 1);
}

static void swap()
{
    test_swap_practical();
    test_swap<int>();
    test_swap<float>();
    test_swap<char>();
    test_swap<char *>();
    test_swap<std::string>();

    display_success("swap");
}

template <typename T>
static void test_clear()
{
    ft::vector<T> vec(DEFAULT_LENGTH);
    ft::vector<T> vec_empty;

    vec.clear();
    vec_empty.clear();

    assert(vec.empty());
    assert(vec_empty.empty());

    for (typename ft::vector<T>::iterator it = vec.begin(); it != vec.end(); it++)
        assert(0);

    for (typename ft::vector<T>::iterator it = vec_empty.begin(); it != vec_empty.end(); it++)
        assert(0);
}

static void clear()
{
    test_clear<int>();
    test_clear<float>();
    test_clear<char>();
    test_clear<char *>();
    test_clear<std::string>();

    display_success("clear");
}

static void test_relational_operators_practical()
{
    ft::vector<int> foo(DEFAULT_LENGTH, 100);
    ft::vector<int> bar(DEFAULT_LENGTH, 200);

    assert(foo < bar);
    assert(foo <= bar);
    assert(bar > foo);
    assert(bar >= foo);
    assert(bar != foo);
    assert(foo != bar);
}

template <typename T>
static void test_relational_operators()
{
    ft::vector<T> foo(DEFAULT_LENGTH);
    ft::vector<T> bar(DEFAULT_LENGTH - 1);

    assert(foo > bar);
    assert(foo >= bar);
    assert(!(foo < bar));
    assert(!(foo <= bar));
    assert(bar < foo);
    assert(bar <= foo);
    assert(bar != foo);
    assert(foo != bar);
    assert(foo == foo);
    assert(bar == bar);
}

static void relational_operators()
{
    test_relational_operators_practical();
    test_relational_operators<int>();

    display_success("relational operators");
}

static void test_swap_non_member_practical()
{
    ft::vector<int> vec_1(DEFAULT_LENGTH * 2, 1);
    ft::vector<int> vec_2(DEFAULT_LENGTH, 2);

    size_t vec_1_cap = vec_1.capacity();
    size_t vec_1_size = vec_1.size();
    size_t vec_2_cap = vec_2.capacity();
    size_t vec_2_size = vec_2.size();

    ft::swap(vec_1, vec_2);

    assert(vec_1.size() == vec_2_size);
    assert(vec_1.capacity() == vec_2_cap);
    assert(vec_2.size() == vec_1_size);
    assert(vec_2.capacity() == vec_1_cap);

    for (size_t i = 0; i < vec_1.size(); i++)
        assert(vec_1[i] == 2);
    for (size_t i = 0; i < vec_2.size(); i++)
        assert(vec_2[i] == 1);
}

template <typename T>
static void test_swap_non_member()
{
    size_t vec_1_size = DEFAULT_LENGTH;
    size_t vec_2_size = DEFAULT_LENGTH * 2;
    ft::vector<T> vec_1(vec_1_size);
    ft::vector<T> vec_2(vec_2_size);

    typename ft::vector<T>::iterator begin_vec_1 = vec_1.begin();
    typename ft::vector<T>::iterator end_vec_1 = vec_1.end();
    typename ft::vector<T>::iterator begin_vec_2 = vec_2.begin();
    typename ft::vector<T>::iterator end_vec_2 = vec_2.end();

    ft::swap(vec_1, vec_2);

    assert(vec_1.size() == vec_2_size);
    assert(vec_2.size() == vec_1_size);
    assert(vec_1.capacity() == vec_2_size);
    assert(vec_2.capacity() == vec_1_size);

    assert(vec_1.begin() == begin_vec_2);
    assert(vec_1.end() == end_vec_2);
    assert(vec_2.begin() == begin_vec_1);
    assert(vec_2.end() == end_vec_1);

    vec_1.push_back(T());

    assert(vec_1.size() == vec_2_size + 1);
    assert(vec_2.size() == vec_1_size);

    vec_2.clear();
    assert(vec_2.empty());
    assert(vec_1.size() == vec_2_size + 1);
}

static void swap_non_member()
{
    test_swap_non_member_practical();
    test_swap_non_member<int>();
    test_swap_non_member<float>();
    test_swap_non_member<char>();
    test_swap_non_member<char *>();
    test_swap_non_member<std::string>();

    display_success("swap");
}

void test_vector()
{
    display("          === vector ===", COLOR_CYAN);

    display("      === Member functions ===", COLOR_RED);

    display("    === Constructors ===", COLOR_YELLOW);
    default_constructor();
    fill_constructor();
    range_constructor();
    copy_constructor();
    assignement_operator();

    display("    === Iterators ===", COLOR_YELLOW);
    begin_end();
    rbegin_rend();

    display("    === Capacity ===", COLOR_YELLOW);
    size();
    max_size();
    resize();
    capacity();
    empty();
    reserve();
    display("    === Element access ===", COLOR_YELLOW);
    access_operator();
    at();
    front_back();

    display("    === Modifiers ===", COLOR_YELLOW);
    assign();
    push_back();
    pop_back();
    insert();
    erase();
    swap();
    clear();

    display("      === Non-member function overloads ===", COLOR_RED);
    relational_operators();
    swap_non_member();
}

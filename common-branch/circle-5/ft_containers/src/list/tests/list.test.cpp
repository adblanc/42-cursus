/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 19:29:57 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:39:11 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test-utils/testUtils.hpp"

template <typename T>
static void test_range_constructor()
{
    std::list<T> list(20, T());
    std::list<T> list_2(list.begin(), list.end());
    ft::list<T> ft_list_2(list.begin(), list.end());
    std::list<T> list_3;

    assert(list_2.size() == 20);
    for (typename std::list<T>::iterator it = list_2.begin(); it != list_2.end(); it++)
    {
        assert(*it == T());
    }

    assert(ft_list_2.size() == 20);
    for (typename ft::list<T>::iterator it = ft_list_2.begin(); it != ft_list_2.end(); it++)
    {
        assert(*it == T());
    }
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
static void test_fill_constructor_no_value()
{
    std::list<T> list(size_t(20));
    ft::list<T> ft_list(size_t(20));

    assert(list.size() == 20);
    assert(ft_list.size() == 20);
    for (typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
    {
        assert(*it == T());
    }

    for (typename ft::list<T>::iterator it = ft_list.begin(); it != ft_list.end(); it++)
    {
        assert(*it == T());
    }
}

template <typename T>
static void test_fill_constructor_with_value()
{
    std::list<T> list(size_t(20), T());
    ft::list<T> ft_list(size_t(20), T());

    assert(list.size() == 20);
    assert(ft_list.size() == 20);
    for (typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
    {
        assert(*it == T());
    }

    for (typename ft::list<T>::iterator it = ft_list.begin(); it != ft_list.end(); it++)
    {
        assert(*it == T());
    }
}

static void fill_constructor()
{
    test_fill_constructor_no_value<int>();
    test_fill_constructor_no_value<float>();
    test_fill_constructor_no_value<double>();
    test_fill_constructor_no_value<std::string>();

    test_fill_constructor_with_value<int>();
    test_fill_constructor_with_value<float>();
    test_fill_constructor_with_value<double>();
    test_fill_constructor_with_value<std::string>();

    display_success("fill constructor");
}

template <typename T>
static void test_copy_constructor()
{
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), T());
    ft_list.insert(ft_list.begin(), T());

    assert(list.size() == 1);
    assert(list.front() == T());

    std::list<T> list_2(list);
    ft::list<T> ft_list_2(ft_list);

    assert(ft_list.size() == 1);
    assert(ft_list.front() == T());

    list_2.clear();
    ft_list_2.clear();

    assert(list_2.size() == 0);
    assert(ft_list_2.size() == 0);
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
static void test_assignement()
{
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), T());
    ft_list.insert(ft_list.begin(), T());

    assert(list.size() == 1);
    assert(ft_list.size() == 1);

    std::list<T> new_list;
    ft::list<T> new_ft_list;

    new_list.insert(new_list.begin(), (size_t)2, T());
    new_ft_list.insert(new_ft_list.begin(), (size_t)2, T());

    list = new_list;
    ft_list = new_ft_list;

    assert(list.size() == 2);
    assert(ft_list.size() == 2);
}

static void assignement_operator()
{
    test_assignement<int>();
    test_assignement<float>();
    test_assignement<double>();
    test_assignement<char>();
    test_assignement<std::string>();

    display_success("assigment operator");
}

template <typename T>
static void test_begin_end()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    assert(list.size() == length);
    assert(ft_list.size() == length);

    size_t listCounter = 0;
    size_t ft_listCounter = 0;

    for (typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
    {
        assert(*it == T());
        listCounter++;
    }
    assert(listCounter == length);

    for (typename ft::list<T>::iterator it = ft_list.begin(); it != ft_list.end(); it++)
    {
        assert(*it == T());
        ft_listCounter++;
    }
    assert(ft_listCounter == length);
}

static void begin_end()
{
    test_begin_end<int>();
    test_begin_end<float>();
    test_begin_end<char>();
    test_begin_end<char *>();
    test_begin_end<std::string>();

    display_success("begin_end");
}

template <typename T>
static void test_rbegin_rend()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    assert(list.size() == length);
    assert(ft_list.size() == length);

    size_t listCounter = 0;
    size_t ft_listCounter = 0;

    for (typename std::list<T>::reverse_iterator it = list.rbegin(); it != list.rend(); it++)
    {
        assert(*it == T());
        listCounter++;
    }
    assert(listCounter == length);

    for (typename ft::list<T>::reverse_iterator it = ft_list.rbegin(); it != ft_list.rend(); it++)
    {
        assert(*it == T());
        ft_listCounter++;
    }
    assert(ft_listCounter == length);
}

static void rbegin_rend()
{
    test_rbegin_rend<int>();
    test_rbegin_rend<float>();
    test_rbegin_rend<char>();
    test_rbegin_rend<char *>();
    test_rbegin_rend<std::string>();

    display_success("rbegin_rend");
}

template <typename T>
static void test_empty()
{
    std::list<T> list;
    ft::list<T> ft_list;

    assert(list.empty() == true);
    assert(ft_list.empty() == true);

    list.insert(list.begin(), T());
    ft_list.insert(ft_list.begin(), T());

    assert(list.empty() == false);
    assert(ft_list.empty() == false);
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
static void test_size()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    for (size_t i = 0; i < length; i++)
    {
        list.push_back(T());
        ft_list.push_back(T());
    }

    assert(list.size() == length);
    assert(ft_list.size() == length);

    list.erase(list.begin());
    ft_list.erase(ft_list.begin());

    assert(list.size() == length - 1);
    assert(ft_list.size() == length - 1);

    list.clear();
    ft_list.clear();

    assert(list.size() == 0);
    assert(ft_list.size() == 0);
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
    ft::list<int> ft_list;

    ft_list.max_size();

    display_success("max_size");
}

template <typename T>
static void test_front()
{
    std::list<T> list;
    ft::list<T> ft_list;
    T list_front_value;
    T ft_list_front_value;

    list.push_front(T());
    ft_list.push_front(T());

    list_front_value = list.front();
    ft_list_front_value = ft_list.front();

    assert(list_front_value == T());
    assert(ft_list_front_value == T());

    list.push_front(T());
    ft_list.push_front(T());

    assert(list.front() == T() && &list.front() != &list_front_value);
    assert(ft_list.front() == T() && &ft_list.front() != &ft_list_front_value);
}

static void front()
{
    test_front<int>();
    test_front<float>();
    test_front<char>();
    test_front<char *>();
    test_front<std::string>();

    display_success("front");
}

template <typename T>
static void test_back()
{
    std::list<T> list;
    ft::list<T> ft_list;
    T list_back;
    T ft_list_back;

    list.push_back(T());
    ft_list.push_back(T());

    list_back = list.back();
    ft_list_back = ft_list.back();

    assert(list_back == T());
    assert(ft_list_back == T());

    list.push_back(T());
    ft_list.push_back(T());

    assert(list.back() == T() && &list.back() != &list_back);
    assert(ft_list.back() == T() && &ft_list.back() != &ft_list_back);
}

static void back()
{
    test_back<int>();
    test_back<float>();
    test_back<char>();
    test_back<char *>();
    test_back<std::string>();

    display_success("back");
}

template <typename T>
static void test_assign()
{
    size_t copyLength = 5;
    T	toCopy_init[] = {T(), T(), T(), T(), T()};

    std::list<T> toCopy(toCopy_init, toCopy_init + 5);
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.end(), (size_t)50, T());
    ft_list.insert(ft_list.end(), (size_t)50, T());

    ft_list.assign(toCopy.begin(), toCopy.end());
    list.assign(toCopy.begin(), toCopy.end());

    assert(list.size() == copyLength);
    assert(ft_list.size() == copyLength);
    for (typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
        assert(*it == T());

    for (typename ft::list<T>::iterator it = ft_list.begin(); it != ft_list.end(); it++)
        assert(*it == T());
}

static void assign()
{
    test_assign<int>();
    test_assign<float>();
    test_assign<char>();
    test_assign<char *>();
    test_assign<std::string>();

    display_success("assign");
}

template <typename T>
static void test_assign_2()
{
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.end(), (size_t)70, T());
    ft_list.insert(ft_list.end(), (size_t)70, T());

    list.assign(size_t(50), T());
    ft_list.assign(size_t(50), T());

    assert(list.size() == 50);
    assert(ft_list.size() == 50);
    for (typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
        assert(*it == T());

    for (typename ft::list<T>::iterator it = ft_list.begin(); it != ft_list.end(); it++)
        assert(*it == T());
}

static void assign_2()
{
    test_assign_2<int>();
    test_assign_2<float>();
    test_assign_2<char>();
    test_assign_2<char *>();
    test_assign_2<std::string>();

    display_success("assign_2");
}

template <typename T>
static void test_push_front()
{
    std::list<T> list;
    ft::list<T> ft_list;

    ft_list.push_front(T());
    ft_list.push_front(T());

    list.push_front(T());
    list.push_front(T());

    assert(*ft_list.begin() == T());
    assert(*--ft_list.end() == T());

    assert(*list.begin() == T());
    assert(*--list.end() == T());

    assert(list.size() == 2);
    assert(ft_list.size() == 2);
}

static void push_front()
{
    test_push_front<int>();
    test_push_front<float>();
    test_push_front<char>();
    test_push_front<char *>();
    test_push_front<std::string>();

    display_success("push_front");
}

template <typename T>
static void test_pop_front()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    assert(list.size() == length);
    assert(ft_list.size() == length);

    for (size_t i = 0; i < length; i++)
    {
        assert(list.size() == length - i);
        assert(ft_list.size() == length - i);
        list.pop_front();
        ft_list.pop_front();
    }

    assert(list.size() == 0);
    assert(ft_list.size() == 0);
    assert(list.empty() == true);
    assert(ft_list.empty() == true);
}

static void pop_front()
{
    test_pop_front<int>();
    test_pop_front<float>();
    test_pop_front<char>();
    test_pop_front<char *>();
    test_pop_front<std::string>();

    display_success("pop_front");
}

template <typename T>
static void test_push_back()
{
    std::list<T> list;
    ft::list<T> ft_list;

    ft_list.push_back(T());
    ft_list.push_back(T());

    list.push_back(T());
    list.push_back(T());

    assert(*ft_list.begin() == T());
    assert(*--ft_list.end() == T());

    assert(*list.begin() == T());
    assert(*--list.end() == T());

    assert(list.size() == 2);
    assert(ft_list.size() == 2);
}

static void push_back()
{
    test_push_back<int>();
    test_push_back<float>();
    test_push_back<char>();
    test_push_back<char *>();
    test_push_back<std::string>();

    display_success("push_back");
}

template <typename T>
static void test_pop_back()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    assert(list.size() == length);
    assert(ft_list.size() == length);

    for (size_t i = 0; i < length; i++)
    {
        assert(list.size() == length - i);
        assert(ft_list.size() == length - i);
        list.pop_back();
        ft_list.pop_back();
    }

    assert(list.size() == 0);
    assert(ft_list.size() == 0);
    assert(list.empty() == true);
    assert(ft_list.empty() == true);
}

static void pop_back()
{
    test_pop_back<int>();
    test_pop_back<float>();
    test_pop_back<char>();
    test_pop_back<char *>();
    test_pop_back<std::string>();

    display_success("pop_back");
}

template <typename T>
static void test_insert()
{
    std::list<T> list;
    ft::list<T> ft_list;

    ft_list.insert(ft_list.begin(), T());
    ft_list.insert(--ft_list.begin(), T());
    ft_list.insert(--ft_list.begin(), T());

    list.insert(list.begin(), T());
    list.insert(--list.begin(), T());
    list.insert(--list.begin(), T());

    assert(*list.begin() == T());
    assert(*++list.begin() == T());
    assert(*--list.end() == T());

    assert(*ft_list.begin() == T());
    assert(*++ft_list.begin() == T());
    assert(*--ft_list.end() == T());
}

static void insert()
{
    test_insert<int>();
    test_insert<float>();
    test_insert<char>();
    test_insert<char *>();
    test_insert<std::string>();

    display_success("insert");
}

template <typename T>
static void test_insert_2()
{
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), (size_t)50, T());
    ft_list.insert(ft_list.begin(), (size_t)50, T());

    assert(list.size() == 50);
    assert(ft_list.size() == 50);

    for (typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
        assert(*it == T());

    for (typename ft::list<T>::iterator it = ft_list.begin(); it != ft_list.end(); it++)
        assert(*it == T());
}

static void insert_2()
{
    test_insert_2<int>();
    test_insert_2<float>();
    test_insert_2<char>();
    test_insert_2<char *>();
    test_insert_2<std::string>();

    display_success("insert_2");
}

template <typename T>
static void test_insert_3()
{
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), (size_t)50, T());
    ft_list.insert(ft_list.begin(), (size_t)50, T());

    assert(list.size() == 50);
    assert(ft_list.size() == 50);

    std::list<T> list_2;
    ft::list<T> ft_list_2;

    list_2.insert(list_2.begin(), list.begin(), list.end());
    ft_list_2.insert(ft_list_2.begin(), list.begin(), list.end());

    assert(list_2.size() == 50);
    assert(ft_list_2.size() == 50);

    for (typename std::list<T>::iterator it = list_2.begin(); it != list_2.end(); it++)
        assert(*it == T());

    for (typename ft::list<T>::iterator it = ft_list_2.begin(); it != ft_list_2.end(); it++)
        assert(*it == T());
}

static void insert_3()
{
    test_insert_3<int>();
    test_insert_3<float>();
    test_insert_3<char>();
    test_insert_3<char *>();
    test_insert_3<std::string>();

    display_success("insert_3");
}

template <typename T>
static void test_erase()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    assert(list.size() == 50);
    assert(ft_list.size() == 50);

    list.erase(list.begin(), list.end());
    ft_list.erase(ft_list.begin(), ft_list.end());

    assert(list.size() == 0);
    assert(ft_list.size() == 0);

    list.push_front(T());
    ft_list.push_front(T());

    list.erase(list.begin());
    ft_list.erase(ft_list.begin());

    assert(list.size() == 0);
    assert(ft_list.size() == 0);
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

template <typename T>
static void test_swap()
{
    size_t listLength = 50;
    size_t listTwoLength = 2;
    std::list<T> list;
    std::list<T> listTwo;

    list.assign(listLength, T());
    listTwo.assign(listTwoLength, T());

    list.swap(listTwo);

    assert(list.size() == listTwoLength);
    assert(listTwo.size() == listLength);

    ft::list<T> ft_list;
    ft::list<T> ft_listTwo;

    ft_list.assign(listLength, T());
    ft_listTwo.assign(listTwoLength, T());

    ft_list.swap(ft_listTwo);

    assert(ft_list.size() == listTwoLength);
    assert(ft_listTwo.size() == listLength);
}

static void swap()
{
    test_swap<int>();
    test_swap<float>();
    test_swap<char>();
    test_swap<char *>();
    test_swap<std::string>();

    display_success("swap");
}

template <typename T>
static void resizeSmallerSize()
{
    std::list<T> list(size_t(5), T());
    ft::list<T> ft_list(size_t(5), T());

    list.resize(2);
    ft_list.resize(2);

    assert(list.size() == 2);
    assert(ft_list.size() == 2);

    for (typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
        assert(*it == T());

    for (typename ft::list<T>::iterator ft_it = ft_list.begin(); ft_it != ft_list.end(); ft_it++)
        assert(*ft_it == T());
}

template <typename T>
static void resizeGreaterSize()
{
    size_t length = 10;
    std::list<T> list;
    ft::list<T> ft_list;

    list.resize(length);
    ft_list.resize(length);

    assert(list.size() == length);
    assert(ft_list.size() == length);

    for (typename std::list<T>::iterator it = list.begin(); it != list.end(); it++)
        assert(*it == T());

    for (typename ft::list<T>::iterator ft_it = ft_list.begin(); ft_it != ft_list.end(); ft_it++)
        assert(*ft_it == T());

    list.resize(20, T());
    ft_list.resize(20, T());

    assert(list.size() == 20);
    assert(ft_list.size() == 20);
}

static void resize()
{
    resizeSmallerSize<int>();
    resizeSmallerSize<float>();
    resizeSmallerSize<char>();
    resizeSmallerSize<char *>();
    resizeSmallerSize<std::string>();

    resizeGreaterSize<int>();
    resizeGreaterSize<float>();
    resizeGreaterSize<char>();
    resizeGreaterSize<char *>();
    resizeGreaterSize<std::string>();

    display_success("resize");
}

template <typename T>
static void test_clear()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());
    assert(list.size() == 50);
    assert(ft_list.size() == 50);

    list.clear();
    ft_list.clear();

    assert(list.size() == 0);
    assert(ft_list.size() == 0);

    list.push_front(T());
    ft_list.push_front(T());

    assert(list.size() == 1);
    assert(ft_list.size() == 1);

    list.clear();
    ft_list.clear();

    assert(list.size() == 0);
    assert(ft_list.size() == 0);
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

template <typename T>
static void test_splice()
{
    size_t length = 50;
    size_t lengthTwo = 20;

    std::list<T> list;
    std::list<T> listTwo;
    ft::list<T> ft_list;
    ft::list<T> ft_listTwo;
    typename std::list<T>::iterator firstIt;
    typename ft::list<T>::iterator ft_firstIt;

    list.insert(list.begin(), length, T());
    listTwo.insert(listTwo.begin(), lengthTwo, T());
    firstIt = list.begin();

    ft_list.insert(ft_list.begin(), length, T());
    ft_listTwo.insert(ft_listTwo.begin(), lengthTwo, T());
    ft_firstIt = ft_list.begin();

    list.splice(list.begin(), listTwo);
    ft_list.splice(ft_list.begin(), ft_listTwo);

    assert(list.size() == length + lengthTwo);
    assert(ft_list.size() == length + lengthTwo);

    assert(listTwo.empty() == true);
    assert(ft_listTwo.empty() == true);

    assert(firstIt != list.begin());
    assert(ft_firstIt != ft_list.begin());
}

static void splice()
{
    test_splice<int>();
    test_splice<float>();
    test_splice<char>();
    test_splice<char *>();
    test_splice<std::string>();

    display_success("splice");
}

template <typename T>
static void test_splice_2()
{
    size_t length = 50;
    size_t lengthTwo = 20;

    std::list<T> list;
    std::list<T> listTwo;
    ft::list<T> ft_list;
    ft::list<T> ft_listTwo;
    typename std::list<T>::iterator firstIt;
    typename ft::list<T>::iterator ft_firstIt;

    list.insert(list.begin(), length, T());
    listTwo.insert(listTwo.begin(), lengthTwo, T());
    firstIt = list.begin();

    ft_list.insert(ft_list.begin(), length, T());
    ft_listTwo.insert(ft_listTwo.begin(), lengthTwo, T());
    ft_firstIt = ft_list.begin();

    list.splice(list.begin(), listTwo, listTwo.begin());
    ft_list.splice(ft_list.begin(), ft_listTwo, ft_listTwo.begin());

    assert(list.size() == length + 1);
    assert(ft_list.size() == length + 1);

    assert(listTwo.size() == lengthTwo - 1);
    assert(ft_listTwo.size() == lengthTwo - 1);

    assert(firstIt != list.begin());
    assert(ft_firstIt != ft_list.begin());
}

static void splice_2()
{
    test_splice_2<int>();
    test_splice_2<float>();
    test_splice_2<char>();
    test_splice_2<char *>();
    test_splice_2<std::string>();

    display_success("splice_2");
}

template <typename T>
static void test_splice_3()
{
    size_t length = 50;
    size_t lengthTwo = 20;

    std::list<T> list;
    std::list<T> listTwo;
    ft::list<T> ft_list;
    ft::list<T> ft_listTwo;
    typename std::list<T>::iterator firstIt;
    typename ft::list<T>::iterator ft_firstIt;

    list.insert(list.begin(), length, T());
    listTwo.insert(listTwo.begin(), lengthTwo, T());
    firstIt = list.begin();

    ft_list.insert(ft_list.begin(), length, T());
    ft_listTwo.insert(ft_listTwo.begin(), lengthTwo, T());
    ft_firstIt = ft_list.begin();

    list.splice(list.begin(), listTwo, listTwo.begin(), listTwo.end());
    ft_list.splice(ft_list.begin(), ft_listTwo, ft_listTwo.begin(), ft_listTwo.end());

    assert(list.size() == length + lengthTwo);
    assert(ft_list.size() == length + lengthTwo);

    assert(listTwo.empty() == true);
    assert(ft_listTwo.empty() == true);

    assert(firstIt != list.begin());
    assert(ft_firstIt != ft_list.begin());
}

static void splice_3()
{
    test_splice_3<int>();
    test_splice_3<float>();
    test_splice_3<char>();
    test_splice_3<char *>();
    test_splice_3<std::string>();

    display_success("splice_3");
}

template <typename T>
static void test_remove()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    list.remove(T());
    ft_list.remove(T());

    assert(list.size() == 0);
    assert(ft_list.size() == 0);

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    assert(list.size() == 50);
    assert(ft_list.size() == 50);
}

static void remove()
{
    test_remove<int>();
    test_remove<float>();
    test_remove<char>();
    test_remove<char *>();
    test_remove<std::string>();

    display_success("remove");
}

template <typename T>
static bool is_default(const T &value)
{
    return (value == T());
}

template <typename T>
static bool is_not_default(const T &value)
{
    return (!is_default(value));
}

template <typename T>
static void test_remove_if()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    list.remove_if(is_not_default<T>);
    ft_list.remove_if(is_not_default<T>);

    assert(list.size() == length);
    assert(ft_list.size() == length);

    list.remove_if(is_default<T>);
    ft_list.remove_if(is_default<T>);

    assert(list.size() == 0);
    assert(ft_list.size() == 0);
}

static void remove_if()
{
    test_remove_if<int>();
    test_remove_if<float>();
    test_remove_if<char>();
    test_remove_if<char *>();
    test_remove_if<std::string>();

    display_success("remove_if");
}

template <typename T>
static void test_unique_remove_duplicates()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    list.unique();
    ft_list.unique();

    assert(list.size() == 1);
    assert(ft_list.size() == 1);
}

static void test_unique_keep_other_values()
{
    std::list<int> list;
    ft::list<int> ft_list;

    list.insert(list.begin(), 1);
    list.insert(list.end(), 2);
    list.insert(list.end(), (size_t)50, 1);

    list.unique();
    assert(list.size() == 3);

    ft_list.insert(ft_list.begin(), 1);
    ft_list.insert(ft_list.end(), 2);
    ft_list.insert(ft_list.end(), (size_t)50, 1);

    ft_list.unique();
    assert(ft_list.size() == 3);
}

static void unique()
{
    test_unique_remove_duplicates<int>();
    test_unique_remove_duplicates<float>();
    test_unique_remove_duplicates<char>();
    test_unique_remove_duplicates<char *>();
    test_unique_remove_duplicates<std::string>();

    test_unique_keep_other_values();

    display_success("unique");
}

template <typename T>
static bool binary_pred_false(T a, T b)
{
    (void)a;
    (void)b;
    return false;
}

template <typename T>
static bool binary_pred_true(T a, T b)
{
    (void)a;
    (void)b;
    return true;
}

template <typename T>
static void test_unique_pred()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    list.unique(binary_pred_false<T>);
    ft_list.unique(binary_pred_false<T>);

    assert(list.size() == length);
    assert(ft_list.size() == length);

    list.unique(binary_pred_true<T>);
    ft_list.unique(binary_pred_true<T>);

    assert(list.size() == 1);
    assert(ft_list.size() == 1);
}

static void unique_pred()
{
    test_unique_pred<int>();
    test_unique_pred<float>();
    test_unique_pred<char>();
    test_unique_pred<char *>();
    test_unique_pred<std::string>();

    display_success("unique_pred");
}

template <typename T>
static void test_sort()
{
    size_t length = 300;
    ft::list<T> ft_list(length);
    ft::list<T> ft_list_2(ft_list);

    assert(ft_list == ft_list_2);

    ft_list.sort();

    assert(ft_list == ft_list_2);

    ft_list_2.sort();

    assert(ft_list == ft_list_2);
}

template <typename T>
static void test_merge()
{
    size_t length = 50;
    size_t length_2 = 25;
    std::list<T> list(length);
    std::list<T> list_2(length_2);
    ft::list<T> ft_list(list.begin(), list.end());
    ft::list<T> ft_list_2(list_2.begin(), list_2.end());
    ft::list<T> ft_list_to_compare(list.begin(), list.end());

    list.merge(list_2);
    ft_list_to_compare.assign(list.begin(), list.end());
    ft_list.merge(ft_list_2);

    assert(list_2.empty() == true);
    assert(ft_list_2.empty() == true);
    assert(ft_list == ft_list_to_compare);

    assert(list.size() == length + length_2);
    assert(ft_list.size() == length + length_2);
}

static void test_merge_practical()
{
    double				array[] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5};
    double				array2[] = {0.5, 1.55, 1.25, 1.75, 6, 2.45, 3.4, 3.7, 4.6, 4.8, 4.9};

    std::list<double> list(array, array + 9);
    std::list<double> list_2(array2, array2 + 11);
    ft::list<double> ft_list(list.begin(), list.end());
    ft::list<double> ft_list_2(list_2.begin(), list_2.end());
    ft::list<double> ft_list_to_compare;

    list.merge(list_2);
    ft_list.merge(ft_list_2);

    ft_list_to_compare.assign(list.begin(), list.end());

    assert(list_2.empty() == true);
    assert(ft_list_2.empty() == true);
    assert(ft_list == ft_list_to_compare);

    ft_list.merge(ft_list);
    assert(ft_list == ft_list_to_compare);
}

static void merge()
{
    test_merge_practical();

    test_merge<int>();
    test_merge<float>();
    test_merge<char>();
    test_merge<char *>();
    test_merge<std::string>();

    display_success("merge");
}

static void test_sort_practical()
{
    std::list<int> a;
    ft::list<int> b;

    for (int i = 0; i < 20; i++)
    {
        a.push_front(i);
        b.push_front(i);
        assert(a.front() == b.front());
    }
    a.sort();
    b.sort();

    ft::list<int>::iterator et = b.begin();

    for (std::list<int>::iterator it = a.begin(); it != a.end(); it++, et++)
        assert(*it == *et);
}

static void sort()
{
    test_sort_practical();
    test_sort<int>();
    test_sort<float>();
    test_sort<char>();
    test_sort<char *>();
    test_sort<std::string>();

    display_success("sort");
}

template <typename T>
static void test_reverse()
{
    size_t length = 50;
    std::list<T> list;
    ft::list<T> ft_list;
    typename std::list<T>::iterator listIt;
    typename ft::list<T>::iterator ft_listIt;

    list.insert(list.begin(), length, T());
    ft_list.insert(ft_list.begin(), length, T());

    listIt = list.begin();
    ft_listIt = ft_list.begin();

    list.reverse();
    ft_list.reverse();

    assert(&(*listIt) == &(*--list.end()));
    assert(&(*ft_listIt) == &(*--ft_list.end()));

    assert(list.size() == length);
    assert(ft_list.size() == length);

    list.clear();
    ft_list.clear();

    list.reverse();
    ft_list.reverse();

    assert(list.empty() == true);
    assert(ft_list.empty() == true);
}

static void reverse()
{
    test_reverse<int>();
    test_reverse<float>();
    test_reverse<char>();
    test_reverse<char *>();
    test_reverse<std::string>();

    display_success("reverse");
}

template <typename T>
static void test_relational_operators_based_on_size()
{
    ft::list<T> a;
    ft::list<T> b;

    a.assign((size_t)50, T());
    b.assign((size_t)25, T());

    assert(a > b);
    assert(a >= b);
    assert(a != b);
    assert(b < a);
    assert(b <= a);

    b.assign(a.begin(), a.end());

    assert(a == b);
}

static void relational_operators()
{
    int	 array_a[] = {10, 20, 30};
    int	 array_b[] = {10, 20, 30};
    int	 array_c[] = {30, 20, 10};
	
    std::list<int> list_a(array_a, array_a + 3);
    std::list<int> list_b(array_b, array_b + 3);
    std::list<int> list_c(array_c, array_c + 3);
    ft::list<int> a(list_a.begin(), list_a.end());
    ft::list<int> b(list_b.begin(), list_b.end());
    ft::list<int> c(list_c.begin(), list_c.end());

    assert(a == b);
    assert(b != c);
    assert(b < c);
    assert(c > b);
    assert(a <= b);
    assert(a >= b);

    test_relational_operators_based_on_size<int>();
    test_relational_operators_based_on_size<float>();
    test_relational_operators_based_on_size<char>();
    test_relational_operators_based_on_size<char *>();
    test_relational_operators_based_on_size<std::string>();

    display_success("relational_operators");
}

template <typename T>
static void test_ft_swap()
{
    size_t listLength = 50;
    size_t listTwoLength = 2;
    std::list<T> list;
    std::list<T> listTwo;

    list.assign(listLength, T());
    listTwo.assign(listTwoLength, T());

    std::swap(list, listTwo);

    assert(list.size() == listTwoLength);
    assert(listTwo.size() == listLength);

    ft::list<T> ft_list;
    ft::list<T> ft_listTwo;

    ft_list.assign(listLength, T());
    ft_listTwo.assign(listTwoLength, T());

    ft::swap(ft_list, ft_listTwo);

    assert(ft_list.size() == listTwoLength);
    assert(ft_listTwo.size() == listLength);
}

static void ft_swap()
{
    test_ft_swap<int>();
    test_ft_swap<float>();
    test_ft_swap<char>();
    test_ft_swap<char *>();
    test_ft_swap<std::string>();

    display_success("ft::swap");
}

void test_list()
{
    display("          === list ===", COLOR_CYAN);

    display("      === Member functions ===", COLOR_RED);

    display("    === Constructors ===", COLOR_YELLOW);

    range_constructor();
    fill_constructor();
    copy_constructor();

    display("    === Assignement operator ===", COLOR_YELLOW);

    assignement_operator();

    display("    === Iterators ===", COLOR_YELLOW);

    begin_end();
    rbegin_rend();

    display("    === Capacity ===", COLOR_YELLOW);

    empty();
    size();
    max_size();

    display("    === Element access ===", COLOR_YELLOW);

    front();
    back();

    display("    === Modifiers ===", COLOR_YELLOW);

    assign();
    assign_2();

    push_front();
    pop_front();

    push_back();
    pop_back();

    insert();
    insert_2();
    insert_3();

    erase();
    swap();
    resize();
    clear();

    display("    === Operations ===", COLOR_YELLOW);

    splice();
    splice_2();
    splice_3();

    remove();
    remove_if();

    unique();
    unique_pred();

    merge();
    sort();

    reverse();

    display("      === Non-member function overloads ===", COLOR_RED);

    relational_operators();
    ft_swap();
}

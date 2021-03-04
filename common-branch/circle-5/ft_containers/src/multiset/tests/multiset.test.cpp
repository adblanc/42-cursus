/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiset.test.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 09:38:10 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:08:21 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Multiset.hpp"
#include "../../test-utils/testUtils.hpp"

template <typename T>
static void test_default_constructor()
{
    ft::multiset<T> a;

    assert(a.empty());

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.size() == i);
        a.insert(T());
    }
}

static void default_constructor()
{
    test_default_constructor<int>();
    test_default_constructor<char>();
    test_default_constructor<float>();
    test_default_constructor<char *>();
    test_default_constructor<std::string>();

    display_success("default constructor");
}

template <typename T>
static void test_range_constructor()
{
    ft::multiset<T> a;

    for (int i = 0; i < 50; i++)
        a.insert(T());
    assert(a.size() == 50);

    ft::multiset<T> b(a.begin(), a.end());

    assert(b.size() == 50);

    b.erase(b.begin());
    assert(b.size() == 49);
    assert(a.size() == 50);
}

static void range_constructor()
{
    test_range_constructor<int>();
    test_range_constructor<char>();
    test_range_constructor<float>();
    test_range_constructor<char *>();
    test_range_constructor<std::string>();

    display_success("range constructor");
}

template <typename T>
static void test_copy_constructor()
{
    ft::multiset<T> a;

    for (int i = 0; i < 50; i++)
        a.insert(T());
    assert(a.size() == 50);

    ft::multiset<T> b(a);

    assert(b.size() == 50);

    b.erase(b.begin());
    assert(b.size() == 49);
    assert(a.size() == 50);
}

static void copy_constructor()
{
    test_copy_constructor<int>();
    test_copy_constructor<char>();
    test_copy_constructor<float>();
    test_copy_constructor<char *>();
    test_copy_constructor<std::string>();

    display_success("copy constructor");
}

template <typename T>
static void test_assignement_operator()
{
    ft::multiset<T> a;

    for (int i = 0; i < 50; i++)
        a.insert(T());
    assert(a.size() == 50);

    ft::multiset<T> b = a;

    assert(b.size() == 50);

    b.erase(b.begin());
    assert(b.size() == 49);
    assert(a.size() == 50);
}

static void assignement_operator()
{
    test_assignement_operator<int>();
    test_assignement_operator<char>();
    test_assignement_operator<float>();
    test_assignement_operator<char *>();
    test_assignement_operator<std::string>();

    display_success("assignement operator");
}

static void test_begin_end_practical()
{
    ft::multiset<int> a;

    for (int i = 0; i < 50; i++)
        a.insert(i);

    assert((*(a.begin())) == 0);
    assert((*(++a.begin())) == 1);

    assert((*(++a.end())) == 0);
    assert((*(--a.end())) == 49);
}

template <typename T>
static void test_begin_end()
{
    ft::multiset<T> a;

    for (int i = 0; i < 50; i++)
        a.insert(T());

    size_t count = 0;
    for (typename ft::multiset<T>::iterator it = a.begin(); it != a.end(); it++)
    {
        assert((*(it)) == T());
        count++;
    }
    assert(count == a.size() && count == 50);
}

static void begin_end()
{
    test_begin_end_practical();
    test_begin_end<int>();
    test_begin_end<char>();
    test_begin_end<float>();
    test_begin_end<char *>();
    test_begin_end<std::string>();

    display_success("begin and end");
}

static void test_rbegin_rend_practical()
{
    ft::multiset<int> a;

    for (int i = 0; i < 50; i++)
        a.insert(i);

    assert((*(a.rbegin())) == 49);
    assert((*(++a.rbegin())) == 48);

    assert((*(--a.rend())) == 0);
}

template <typename T>
static void test_rbegin_rend()
{

    ft::multiset<T> a;

    for (int i = 0; i < 50; i++)
        a.insert(T());

    size_t count = 0;
    for (typename ft::multiset<T>::reverse_iterator it = a.rbegin(); it != a.rend(); it++)
    {
        assert((*(it)) == T());
        count++;
    }
    assert(count == a.size() && count == 50);
}

static void rbegin_rend()
{
    test_rbegin_rend_practical();
    test_rbegin_rend<int>();
    test_rbegin_rend<char>();
    test_rbegin_rend<float>();
    test_rbegin_rend<char *>();
    test_rbegin_rend<std::string>();

    display_success("rbegin_rend");
}

template <typename T>
static void test_empty()
{
    ft::multiset<T> a;

    assert(a.empty());

    a.insert(T());
    assert(!a.empty());

    a.erase(a.begin());
    assert(a.empty());

    for (int i = 0; i < 50; i++)
        a.insert(T());

    a.erase(a.begin(), a.end());

    assert(a.empty());
}

static void empty()
{
    test_empty<int>();
    test_empty<char>();
    test_empty<float>();
    test_empty<char *>();
    test_empty<std::string>();

    display_success("empty");
}

template <typename T>
static void test_size()
{
    ft::multiset<T> a;

    assert(a.size() == 0);

    for (int i = 0; i < 50; i++)
        a.insert(T());
    assert(a.size() == 50);

    a.erase(a.begin());
    assert(a.size() == 49);
    a.clear();
    assert(a.size() == 0);
    assert(a.empty());
}

static void size()
{
    test_size<int>();
    test_size<char>();
    test_size<float>();
    test_size<char *>();
    test_size<std::string>();

    display_success("size");
}

static void max_size()
{
    ft::multiset<int> a;

    a.max_size();

    display_success("max_size");
}

static void test_insert_single_practical()
{
    ft::multiset<int> a;

    a.insert(5);
    assert(a.size() == 1);
    a.insert(5);
    assert(a.size() == 2);
    a.insert(5);
    assert(a.size() == 3);
    a.insert(6);
    assert(a.size() == 4);
}

static void test_insert_range_practical()
{
    ft::multiset<int> a;

    a.insert(5);
    a.insert(6);
    a.insert(5);
    a.insert(6);

    assert(a.size() == 4);

    ft::multiset<int> b;

    b.insert(a.begin(), a.end());

    assert(b.size() == 4);
    b.insert(a.begin(), a.end());
    assert(b.size() == 8);
}

static void test_insert_hint_practical()
{
    ft::multiset<int> a;

    a.insert(a.begin(), 5);

    assert(a.size() == 1);
    a.insert(a.begin(), 6);
    assert(a.size() == 2);

    a.insert(a.begin(), 6);
    assert(a.size() == 3);
}

static void test_insert_practical()
{
    test_insert_single_practical();
    test_insert_range_practical();
    test_insert_hint_practical();
}

template <typename T>
static void test_insert()
{
    ft::multiset<T> a;
    ft::multiset<T> empty;

    a.insert(T());
    assert(a.size() == 1);
    a.insert(T());
    assert(a.size() == 2);

    ft::multiset<T> b;

    b.insert(empty.begin(), empty.end());
    assert(b.empty());

    b.insert(a.begin(), a.end());
    assert(b.size() == a.size());

    b.insert(a.begin(), a.end());
    assert(b.size() == a.size() * 2);
}

static void insert()
{
    test_insert_practical();
    test_insert<int>();
    test_insert<char>();
    test_insert<float>();
    test_insert<char *>();
    test_insert<std::string>();

    display_success("insert");
}

static void test_erase_practical()
{
    ft::multiset<int> a;

    a.insert(a.begin(), 1);
    a.insert(a.begin(), 1);
    a.insert(a.begin(), 2);
    a.insert(a.begin(), 3);

    assert((*(a.begin())) == 1);
    assert(a.size() == 4);

    a.erase(a.begin());

    assert((*(a.begin())) == 1);
    assert(a.size() == 3);

    a.erase(a.begin());

    assert((*(a.begin())) == 2);
    assert(a.size() == 2);

    a.erase(a.begin());

    assert((*(a.begin())) == 3);

    assert(a.size() == 1);

    a.erase(a.begin());
    assert(a.empty());
}

template <typename T>
static void test_erase()
{
    ft::multiset<T> a;

    a.insert(T());
    a.erase(a.begin());

    assert(a.empty());
    a.erase(a.begin());
    a.erase(a.end());
    assert(a.empty());
}

static void test_erase_key_practical()
{
    ft::multiset<int> a;

    a.insert(a.begin(), 1);
    a.insert(a.begin(), 1);
    a.insert(a.begin(), 2);
    a.insert(a.begin(), 4);

    assert(a.erase(1) == 2);
    assert(a.erase(1) == 0);

    assert(a.erase(2) == 1);
    assert(a.erase(2) == 0);

    assert(a.erase(4) == 1);
    assert(a.erase(4) == 0);

    assert(a.erase(6) == 0);
    assert(a.erase(7) == 0);
    assert(a.empty());
}

template <typename T>
static void test_erase_key()
{
    ft::multiset<T> a;

    for (int i = 0; i < 50; i++)
        a.insert(T());

    assert(a.erase(T()) == 50);

    assert(a.empty());
    assert(a.erase(T()) == 0);
    assert(a.empty());
}

static void test_erase_range_practical()
{
    ft::multiset<int> a;

    a.insert(a.begin(), 1);
    a.insert(a.begin(), 2);
    a.insert(a.begin(), 5);
    a.insert(a.begin(), 3);
    a.insert(a.begin(), 4);

    a.erase(a.begin(), ++a.begin());
    assert(a.size() == 4);
    assert((*(a.begin())) == 2);

    a.erase(a.begin(), a.end());
    assert(a.empty());
}

template <typename T>
static void test_erase_range()
{
    ft::multiset<T> a;

    a.erase(a.begin(), a.end());
    for (int i = 0; i < 50; i++)
        a.insert(T());
    a.erase(a.begin(), a.end());

    assert(a.empty());
}
static void erase()
{
    test_erase_practical();
    test_erase_range_practical();
    test_erase_key_practical();

    test_erase<int>();
    test_erase<char>();
    test_erase<float>();
    test_erase<char *>();
    test_erase<std::string>();

    test_erase_key<int>();
    test_erase_key<char>();
    test_erase_key<float>();
    test_erase_key<char *>();
    test_erase_key<std::string>();

    test_erase_range<int>();
    test_erase_range<char>();
    test_erase_range<float>();
    test_erase_range<char *>();
    test_erase_range<std::string>();

    display_success("erase");
}

static void test_swap_practical()
{
    ft::multiset<int> a;

    a.insert(a.begin(), 1);
    a.insert(a.begin(), 2);
    a.insert(a.begin(), 3);
    a.insert(a.begin(), 4);
    a.insert(a.begin(), 5);

    ft::multiset<int> b;

    a.swap(b);

    assert(b.size() == 5);
    assert(a.empty());

    assert((*(b.begin())) == 1);
    assert((*(++b.begin())) == 2);
    assert((*(--b.end())) == 5);
}

template <typename T>
static void test_swap()
{
    ft::multiset<T> a;
    ft::multiset<T> b;

    for (int i = 0; i < 50; i++)
        a.insert(T());

    assert(a.size() == 50);
    assert((*(a.begin())) == T());
    assert((*(--a.end())) == T());
    assert(b.empty());

    a.swap(b);

    assert(b.size() == 50);
    assert((*(b.begin())) == T());
    assert((*(--b.end())) == T());
    assert(a.empty());
}

static void swap()
{
    test_swap_practical();
    test_swap<int>();
    test_swap<char>();
    test_swap<float>();
    test_swap<char *>();
    test_swap<std::string>();

    display_success("swap");
}

static void test_clear_practical()
{
    ft::multiset<int> a;

    a.clear();
    assert(a.empty());

    for (int i = 0; i < 50; i++)
        a.insert(i);
    for (int i = 0; i < 50; i++)
        a.insert(i);

    assert(a.size() == 100);

    a.clear();

    assert(a.empty());
}

template <typename T>
static void test_clear()
{
    ft::multiset<T> a;

    a.clear();

    a.insert(T());

    a.clear();
    assert(a.empty());

    for (int i = 0; i < 50; i++)
        a.insert(T());

    assert(a.size() == 50);

    a.clear();
    assert(a.empty());

    a.clear();
    assert(a.empty());
}

static void clear()
{
    test_clear_practical();
    test_clear<int>();
    test_clear<char>();
    test_clear<float>();
    test_clear<char *>();
    test_clear<std::string>();

    display_success("clear");
}

static void test_find_practical()
{
    ft::multiset<int> a;

    a.insert(1);
    a.insert(2);
    a.insert(4);

    assert(*a.find(1) == 1);

    a.clear();
    assert(a.empty());

    for (int i = 0; i < 50; i++)
    {
        assert(a.find(i) == a.end());
        a.insert(i);
        assert(a.find(i) != a.end());
    }
}

template <typename T>
static void test_find()
{
    ft::multiset<T> a;

    assert(a.find(T()) == a.end());

    for (int i = 0; i < 50; i++)
        a.insert(T());

    assert(a.find(T()) != a.end());

    const ft::multiset<T> b(a);

    assert(b.find(T()) != b.end());
}

static void find()
{
    test_find_practical();
    test_find<int>();
    test_find<char>();
    test_find<float>();
    test_find<char *>();
    test_find<std::string>();

    display_success("find");
}

static void test_count_practical()
{
    ft::multiset<int> a;

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.count(i) == 0);
        a.insert(i);
        assert(a.count(i) == 1);
    }

    a.clear();

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.count(0) == i);
        a.insert(0);
    }
}

template <typename T>
static void test_count()
{
    ft::multiset<T> a;

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.count(T()) == i);
        a.insert(T());
    }
}

static void count()
{
    test_count_practical();
    test_count<int>();
    test_count<char>();
    test_count<float>();
    test_count<char *>();
    test_count<std::string>();

    display_success("count");
}

static void test_lower_bound_practical()
{
    ft::multiset<int> a;

    a.insert(1);
    a.insert(1);
    a.insert(3);
    a.insert(4);

    assert(a.lower_bound(1) == a.begin());
    assert(a.lower_bound(4) == --a.end());
    assert(a.lower_bound(66) == a.end());
}

template <typename T>
static void test_lower_bound()
{
    ft::multiset<T> a;

    assert(a.lower_bound(T()) == a.end());

    a.insert(T());

    assert(a.lower_bound(T()) == a.begin());
    assert((*(a.lower_bound(T()))) == T());

    const ft::multiset<T> b(a);

    assert(b.lower_bound(T()) == b.begin());
    assert((*(b.lower_bound(T()))) == T());
}

static void lower_bound()
{
    test_lower_bound_practical();
    test_lower_bound<int>();
    test_lower_bound<char>();
    test_lower_bound<float>();
    test_lower_bound<char *>();
    test_lower_bound<std::string>();

    display_success("lower_bound");
}

static void test_upper_bound_practical()
{
    ft::multiset<int> a;

    a.insert(1);
    a.insert(1);
    a.insert(2);
    a.insert(3);

    assert((*(a.upper_bound(1))) == 2);
    assert(a.upper_bound(2) == --a.end());
    assert(a.upper_bound(3) == a.end());
}

template <typename T>
static void test_upper_bound()
{
    ft::multiset<T> a;

    assert(a.upper_bound(T()) == a.end());

    for (size_t i = 0; i < 50; i++)
        a.insert(T());

    assert(a.upper_bound(T()) == a.end());

    const ft::multiset<T> b(a);

    assert(b.upper_bound(T()) == b.end());
}

static void upper_bound()
{
    test_upper_bound_practical();
    test_upper_bound<int>();
    test_upper_bound<char>();
    test_upper_bound<float>();
    test_upper_bound<char *>();
    test_upper_bound<std::string>();

    display_success("upper_bound");
}

static void test_equal_range_practical()
{
    ft::multiset<int> mymm;

    mymm.insert(10);
    mymm.insert(20);
    mymm.insert(20);
    mymm.insert(20);
    mymm.insert(50);
    mymm.insert(60);
    mymm.insert(60);

    assert(*(mymm.equal_range(10).first) == 10);
    assert(*(mymm.equal_range(10).second) == 20);

    assert(*(mymm.equal_range(20).first) == 20);
    assert(*(mymm.equal_range(20).second) == 50);

    assert(*(mymm.equal_range(30).first) == 50);
    assert(*(mymm.equal_range(30).second) == 50);

    assert(*(mymm.equal_range(60).first) == 60);
    assert(mymm.equal_range(60).second == mymm.end());
}

static void equal_range()
{
    test_equal_range_practical();

    display_success("equal_range");
}

void test_multiset()
{
    display("          === multiset ===", COLOR_CYAN);

    display("      === Member functions ===", COLOR_RED);

    display("    === Constructors ===", COLOR_YELLOW);
    default_constructor();
    range_constructor();
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

    display("    === Modifiers ===", COLOR_YELLOW);
    insert();
    erase();
    swap();
    clear();

    display("    === Operations ===", COLOR_YELLOW);
    find();
    count();
    lower_bound();
    upper_bound();
    equal_range();
}

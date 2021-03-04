/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 11:23:28 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:08:42 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Set.hpp"
#include "../../test-utils/testUtils.hpp"

template <typename T>
static void test_default_constructor()
{
    ft::set<T> a;

    assert(a.empty());

    a.insert(T());
    assert(a.size());

    for (int i = 0; i < 50; i++)
    {
        assert(a.insert(T()).second == false);
        assert(a.insert(T()).first == a.begin());
    }
    assert(a.size() == 1);
}

static void default_constructor()
{
    test_default_constructor<char>();
    test_default_constructor<int>();
    test_default_constructor<float>();
    test_default_constructor<char *>();
    test_default_constructor<std::string>();

    display_success("default constructor");
}

template <typename T>
static void test_range_constructor()
{
    ft::set<T> a;

    a.insert(T());
    assert(a.size() == 1);

    ft::set<T> b(a.begin(), a.end());

    assert(b.size() == 1);

    b.erase(b.begin());
    assert(b.empty());
    assert(a.size() == 1);
}

static void range_constructor()
{
    test_range_constructor<char>();
    test_range_constructor<int>();
    test_range_constructor<float>();
    test_range_constructor<char *>();
    test_range_constructor<std::string>();

    display_success("range constructor");
}

template <typename T>
static void test_copy_constructor()
{
    ft::set<T> a;

    a.insert(T());
    assert(a.size() == 1);

    ft::set<T> b(a);

    assert(b.size() == 1);

    b.erase(b.begin());
    assert(b.empty());
    assert(a.size() == 1);
}

static void copy_constructor()
{
    test_copy_constructor<char>();
    test_copy_constructor<int>();
    test_copy_constructor<float>();
    test_copy_constructor<char *>();
    test_copy_constructor<std::string>();

    display_success("copy constructor");
}

template <typename T>
static void test_assignement_operator()
{
    ft::set<T> a;
    ft::set<T> b;

    a = b;

    assert(a.empty());
    assert(b.empty());

    a.insert(T());

    b = a;

    assert(a.size() == 1);
    assert(b.size() == 1);

    a.erase(a.begin());

    assert(a.empty());
    assert(b.size() == 1);
}

static void assignement_operator()
{
    test_assignement_operator<char>();
    test_assignement_operator<int>();
    test_assignement_operator<float>();
    test_assignement_operator<char *>();
    test_assignement_operator<std::string>();

    display_success("assignement operator");
}

static void test_begin_end_practical()
{
    ft::set<int> a;

    a.insert(1);
    a.insert(2);

    assert(*(a.begin()) == 1);
    assert(*(++a.begin()) == 2);

    assert(*(--a.end()) == 2);
    assert(*(++a.end()) == 1);
}

template <typename T>
static void test_begin_end()
{
    ft::set<T> a;

    a.insert(T());

    size_t count = 0;
    for (typename ft::set<T>::iterator it = a.begin(); it != a.end(); it++)
    {
        assert(*(it) == T());
        count++;
    }
    assert(count == a.size() && count == 1);
}

static void begin_end()
{
    test_begin_end_practical();
    test_begin_end<char>();
    test_begin_end<int>();
    test_begin_end<float>();
    test_begin_end<char *>();
    test_begin_end<std::string>();

    display_success("begin and end");
}

static void test_rbegin_rend_practical()
{
    ft::set<int> a;

    a.insert(1);
    a.insert(2);

    assert(*(a.rbegin()) == 2);
    assert(*(++a.rbegin()) == 1);
    assert(*(--a.rend()) == 1);
}

template <typename T>
static void test_rbegin_rend()
{
    ft::set<T> a;

    a.insert(T());

    size_t count = 0;
    for (typename ft::set<T>::reverse_iterator it = a.rbegin(); it != a.rend(); it++)
    {
        assert(*(it) == T());
        count++;
    }
    assert(count == a.size() && count == 1);
}

static void rbegin_rend()
{
    test_rbegin_rend_practical();
    test_rbegin_rend<char>();
    test_rbegin_rend<int>();
    test_rbegin_rend<float>();
    test_rbegin_rend<char *>();
    test_rbegin_rend<std::string>();

    display_success("rbegin_rend");
}

template <typename T>
static void test_empty()
{
    ft::set<T> a;

    assert(a.empty());

    a.insert(T());
    assert(!a.empty());

    a.erase(a.begin());
    assert(a.empty());
}

static void empty()
{
    test_empty<char>();
    test_empty<int>();
    test_empty<float>();
    test_empty<char *>();
    test_empty<std::string>();

    display_success("empty");
}

template <typename T>
static void test_size()
{
    ft::set<T> a;

    assert(a.size() == 0);

    for (int i = 0; i < 50; i++)
        a.insert(T());
    assert(a.size() == 1);

    a.erase(a.begin());
    assert(a.size() == 0);
}

static void size()
{
    test_size<char>();
    test_size<int>();
    test_size<float>();
    test_size<char *>();
    test_size<std::string>();

    display_success("size");
}

static void max_size()
{
    ft::set<int> a;

    a.max_size();

    display_success("max_size");
}

static void test_insert_single_practical()
{
    ft::set<int> a;

    a.insert(1);
    assert(a.size() == 1);
    a.insert(1);
    assert(a.size() == 1);
    a.insert(1);
    assert(a.size() == 1);
    a.insert(2);
    assert(a.size() == 2);
}

static void test_insert_range_practical()
{
    ft::set<int> a;

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    assert(a.size() == 4);

    ft::set<int> b;

    b.insert(a.begin(), a.end());

    assert(b.size() == 4);
    b.insert(a.begin(), a.end());
    assert(b.size() == 4);
}

static void test_insert_hint_practical()
{
    ft::set<int> a;

    a.insert(a.begin(), 1);

    assert(a.size() == 1);

    a.insert(a.begin(), 1);
    assert(a.size() == 1);

    a.insert(a.begin(), 2);
    assert(a.size() == 2);
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
    ft::set<T> a;
    ft::set<T> empty;

    a.insert(T());
    assert(a.size() == 1);
    a.insert(T());
    assert(a.size() == 1);

    ft::set<T> b;

    b.insert(empty.begin(), empty.end());
    assert(b.empty());

    b.insert(a.begin(), a.end());
    assert(b.size() == 1);

    b.insert(a.begin(), a.end());
    assert(b.size() == 1);
}

static void insert()
{
    test_insert_practical();
    test_insert<char>();
    test_insert<int>();
    test_insert<float>();
    test_insert<char *>();
    test_insert<std::string>();

    display_success("insert");
}

static void test_erase_practical()
{
    ft::set<int> a;

    a.insert(a.begin(), 1);
    a.insert(a.begin(), 2);
    a.insert(a.begin(), 3);
    a.insert(a.begin(), 4);

    assert((*(a.begin())) == 1);
    assert(a.size() == 4);

    a.erase(a.begin());

    assert((*(a.begin())) == 2);

    a.erase(a.begin());

    assert((*(a.begin())) == 3);

    a.erase(a.begin());

    assert((*(a.begin())) == 4);
}

template <typename T>
static void test_erase()
{
    ft::set<T> a;

    a.insert(T());
    a.erase(a.begin());

    assert(a.empty());
    a.erase(a.begin());
    a.erase(a.end());
    assert(a.empty());
}

static void test_erase_key_practical()
{
    ft::set<int> a;

    a.insert(a.begin(), 1);
    a.insert(a.begin(), 2);
    a.insert(a.begin(), 3);
    a.insert(a.begin(), 4);

    assert(a.erase(1) == 1);
    assert(a.erase(1) == 0);

    assert(a.erase(2) == 1);
    assert(a.erase(2) == 0);

    assert(a.erase(3) == 1);
    assert(a.erase(3) == 0);

    assert(a.erase(4) == 1);
    assert(a.erase(4) == 0);

    assert(a.erase(10) == 0);
    assert(a.empty());
}

template <typename T>
static void test_erase_key()
{
    ft::set<T> a;

    a.insert(T());
    assert(a.erase(T()) == 1);

    assert(a.empty());
    assert(a.erase(T()) == 0);
    assert(a.empty());
}

static void test_erase_range_practical()
{
    ft::set<int> a;

    a.insert(a.begin(), 1);
    a.insert(a.begin(), 2);
    a.insert(a.begin(), 3);
    a.insert(a.begin(), 4);

    a.erase(a.begin(), ++a.begin());
    assert((*(a.begin())) == 2);

    a.erase(a.begin(), a.end());
    assert(a.empty());
}

template <typename T>
static void test_erase_range()
{
    ft::set<T> a;

    a.erase(a.begin(), a.end());

    a.insert(T());

    a.erase(a.begin(), a.end());
    assert(a.empty());
    a.erase(a.begin(), a.end());
    assert(a.empty());
}
static void erase()
{
    test_erase_practical();
    test_erase_range_practical();
    test_erase_key_practical();

    test_erase<char>();
    test_erase<int>();
    test_erase<float>();
    test_erase<char *>();
    test_erase<std::string>();

    test_erase_key<char>();
    test_erase_key<int>();
    test_erase_key<float>();
    test_erase_key<char *>();
    test_erase_key<std::string>();

    test_erase_range<char>();
    test_erase_range<int>();
    test_erase_range<float>();
    test_erase_range<char *>();
    test_erase_range<std::string>();

    display_success("erase");
}

static void test_swap_practical()
{
    ft::set<int> a;

    a.insert(a.begin(), 1);
    a.insert(a.begin(), 2);
    a.insert(a.begin(), 3);
    a.insert(a.begin(), 4);

    ft::set<int> b;

    a.swap(b);

    assert(b.size() == 4);
    assert(a.empty());
}

template <typename T>
static void test_swap()
{
    ft::set<T> a;
    ft::set<T> b;

    a.insert(T());

    assert(a.size() == 1);
    assert((*(a.begin())) == T());
    assert((*(--a.end())) == T());
    assert(b.empty());

    a.swap(b);

    assert(b.size() == 1);
    assert((*(b.begin())) == T());
    assert((*(--b.end())) == T());
    assert(a.empty());
}

static void swap()
{
    test_swap_practical();
    test_swap<char>();
    test_swap<int>();
    test_swap<float>();
    test_swap<char *>();
    test_swap<std::string>();

    display_success("swap");
}

static void test_clear_practical()
{
    ft::set<int> a;

    for (int i = 0; i < 50; i++)
        a.insert(i);

    assert(a.size() == 50);

    a.clear();

    assert(a.empty());
}

template <typename T>
static void test_clear()
{
    ft::set<T> a;

    a.insert(T());
    assert(a.size() == 1);

    a.clear();

    assert(a.empty());

    a.insert(T());
    assert(a.size() == 1);
    a.clear();
    assert(a.empty());
}

static void clear()
{
    test_clear_practical();
    test_clear<char>();
    test_clear<int>();
    test_clear<float>();
    test_clear<char *>();
    test_clear<std::string>();

    display_success("clear");
}

static void test_find_practical()
{
    ft::set<int> a;

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.find(i) == a.end());
        a.insert(i);
        assert(a.find(i) != a.end());
    }
}

template <typename T>
static void test_find()
{
    ft::set<T> a;

    assert(a.find(T()) == a.end());

    a.insert(T());
    assert(a.size() == 1);

    assert(a.find(T()) == a.begin());
    assert(a.find(T()) == --a.end());

    const ft::set<T> b(a);

    assert(b.size() == 1);
    assert(b.find(T()) == b.begin());
    assert(b.find(T()) == --b.end());
}

static void find()
{
    test_find_practical();
    test_find<char>();
    test_find<int>();
    test_find<float>();
    test_find<char *>();
    test_find<std::string>();

    display_success("find");
}

static void test_count_practical()
{
    ft::set<int> a;

    for (int i = 0; i < 50; i++)
    {
        assert(a.count(i) == 0);
        a.insert(i);
        assert(a.count(i) == 1);
    }
    assert(a.count(50) == 0);

    a.clear();
    for (int i = 0; i < 50; i++)
        assert(a.count(i) == 0);
}

template <typename T>
static void test_count()
{
    ft::set<T> a;

    assert(a.count(T()) == 0);

    a.insert(T());
    assert(a.count(T()) == 1);

    a.erase(a.begin());

    assert(a.count(T()) == 0);
}

static void count()
{
    test_count_practical();
    test_count<char>();
    test_count<int>();
    test_count<float>();
    test_count<char *>();
    test_count<std::string>();

    display_success("count");
}

static void test_lower_bound_practical()
{
    ft::set<int> a;

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    assert(a.lower_bound(0) == a.begin());
    assert(a.lower_bound(1) == a.begin());
    assert(a.lower_bound(4) == --a.end());
    assert(a.lower_bound(5) == a.end());
}

template <typename T>
static void test_lower_bound()
{
    ft::set<T> a;

    assert(a.lower_bound(T()) == a.end());

    a.insert(T());
    assert(a.lower_bound(T()) == a.begin());

    assert((*(a.lower_bound(T()))) == T());

    const ft::set<T> b(a);

    assert(b.lower_bound(T()) == b.begin());
    assert((*(b.lower_bound(T()))) == T());
}

static void lower_bound()
{
    test_lower_bound_practical();
    test_lower_bound<char>();
    test_lower_bound<int>();
    test_lower_bound<float>();
    test_lower_bound<char *>();
    test_lower_bound<std::string>();

    display_success("lower_bound");
}

static void test_upper_bound_practical()
{
    ft::set<int> a;

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    assert(a.upper_bound(0) == a.begin());
    assert(a.upper_bound(1) == ++a.begin());
    assert(a.upper_bound(4) == a.end());
    assert(a.upper_bound(5) == a.end());
}

template <typename T>
static void test_upper_bound()
{
    ft::set<T> a;

    assert(a.upper_bound(T()) == a.end());

    a.insert(T());
    assert(a.upper_bound(T()) == a.end());

    const ft::set<T> b(a);

    assert(b.upper_bound(T()) == b.end());
}

static void upper_bound()
{
    test_upper_bound_practical();
    test_upper_bound<char>();
    test_upper_bound<int>();
    test_upper_bound<float>();
    test_upper_bound<char *>();
    test_upper_bound<std::string>();

    display_success("upper_bound");
}

static void test_equal_range_practical()
{
    ft::set<int> a;

    a.insert(10);
    a.insert(20);
    a.insert(30);

    ft::Pair<ft::set<int>::iterator, ft::set<int>::iterator> ret;
    ret = a.equal_range(20);

    assert(*ret.first == 20);
    assert(*ret.second == 30);

    ret = a.equal_range(30);

    assert(*ret.first == 30);
    assert(ret.second == a.end());

    a.insert(50);

    ret = a.equal_range(40);

    assert(*ret.first == 50);
    assert(*ret.second == 50);
}

static void equal_range()
{
    test_equal_range_practical();

    display_success("equal_range");
}

void test_set()
{
    display("          === set ===", COLOR_CYAN);

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

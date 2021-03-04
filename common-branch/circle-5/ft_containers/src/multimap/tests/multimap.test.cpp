/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multimap.test.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 09:38:10 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:06:55 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Multimap.hpp"
#include "../../test-utils/testUtils.hpp"

template <typename T1, typename T2>
static void test_default_constructor()
{
    ft::multimap<T1, T2> a;

    assert(a.empty());

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.size() == i);
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    }
}

static void default_constructor()
{
    test_default_constructor<char, int>();
    test_default_constructor<int, int>();
    test_default_constructor<float, char>();
    test_default_constructor<char *, int>();
    test_default_constructor<int, std::string>();

    display_success("default constructor");
}

template <typename T1, typename T2>
static void test_range_constructor()
{
    ft::multimap<T1, T2> a;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    assert(a.size() == 50);

    ft::multimap<T1, T2> b(a.begin(), a.end());

    assert(b.size() == 50);

    b.erase(b.begin());
    assert(b.size() == 49);
    assert(a.size() == 50);
}

static void range_constructor()
{
    test_range_constructor<char, int>();
    test_range_constructor<int, int>();
    test_range_constructor<float, char>();
    test_range_constructor<char *, int>();
    test_range_constructor<int, std::string>();

    display_success("range constructor");
}

template <typename T1, typename T2>
static void test_copy_constructor()
{
    ft::multimap<T1, T2> a;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    assert(a.size() == 50);

    ft::multimap<T1, T2> b(a);

    assert(b.size() == 50);

    b.erase(b.begin());
    assert(b.size() == 49);
    assert(a.size() == 50);
}

static void copy_constructor()
{
    test_copy_constructor<char, int>();
    test_copy_constructor<int, int>();
    test_copy_constructor<float, char>();
    test_copy_constructor<char *, int>();
    test_copy_constructor<int, std::string>();

    display_success("copy constructor");
}

template <typename T1, typename T2>
static void test_assignement_operator()
{
    ft::multimap<T1, T2> a;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    assert(a.size() == 50);

    ft::multimap<T1, T2> b = a;

    assert(b.size() == 50);

    b.erase(b.begin());
    assert(b.size() == 49);
    assert(a.size() == 50);
}

static void assignement_operator()
{
    test_assignement_operator<char, int>();
    test_assignement_operator<int, int>();
    test_assignement_operator<float, char>();
    test_assignement_operator<char *, int>();
    test_assignement_operator<int, std::string>();

    display_success("assignement operator");
}

static void test_begin_end_practical()
{
    ft::multimap<char, int> a;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<char, int>(i, i));

    assert((*(a.begin())).first == 0);
    assert((*(++a.begin())).first == 1);

    assert((*(++a.end())).first == 0);
    assert((*(--a.end())).first == 49);
}

template <typename T1, typename T2>
static void test_begin_end()
{
    ft::multimap<T1, T2> a;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    size_t count = 0;
    for (typename ft::multimap<T1, T2>::iterator it = a.begin(); it != a.end(); it++)
    {
        assert((*(it)).first == T1());
        assert((*(it)).second == T2());
        count++;
    }
    assert(count == a.size() && count == 50);
}

static void begin_end()
{
    test_begin_end_practical();
    test_begin_end<char, int>();
    test_begin_end<int, int>();
    test_begin_end<float, char>();
    test_begin_end<char *, int>();
    test_begin_end<int, std::string>();

    display_success("begin and end");
}

static void test_rbegin_rend_practical()
{
    ft::multimap<char, int> a;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<char, int>(i, i));

    assert((*(a.rbegin())).first == 49);
    assert((*(++a.rbegin())).first == 48);

    assert((*(--a.rend())).first == 0);
}

template <typename T1, typename T2>
static void test_rbegin_rend()
{

    ft::multimap<T1, T2> a;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    size_t count = 0;
    for (typename ft::multimap<T1, T2>::reverse_iterator it = a.rbegin(); it != a.rend(); it++)
    {
        assert((*(it)).first == T1());
        assert((*(it)).second == T2());
        count++;
    }
    assert(count == a.size() && count == 50);
}

static void rbegin_rend()
{
    test_rbegin_rend_practical();
    test_rbegin_rend<char, int>();
    test_rbegin_rend<int, int>();
    test_rbegin_rend<float, char>();
    test_rbegin_rend<char *, int>();
    test_rbegin_rend<int, std::string>();

    display_success("rbegin_rend");
}

template <typename T1, typename T2>
static void test_empty()
{
    ft::multimap<T1, T2> a;

    assert(a.empty());

    a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    assert(!a.empty());

    a.erase(a.begin());
    assert(a.empty());

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    a.erase(a.begin(), a.end());

    assert(a.empty());
}

static void empty()
{
    test_empty<char, int>();
    test_empty<int, int>();
    test_empty<float, char>();
    test_empty<char *, int>();
    test_empty<int, std::string>();

    display_success("empty");
}

template <typename T1, typename T2>
static void test_size()
{
    ft::multimap<T1, T2> a;

    assert(a.size() == 0);

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    assert(a.size() == 50);

    a.erase(a.begin());
    assert(a.size() == 49);
    a.clear();
    assert(a.size() == 0);
    assert(a.empty());
}

static void size()
{
    test_size<char, int>();
    test_size<int, int>();
    test_size<float, char>();
    test_size<char *, int>();
    test_size<int, std::string>();

    display_success("size");
}

static void max_size()
{
    ft::multimap<char, int> a;

    a.max_size();

    display_success("max_size");
}

static void test_insert_single_practical()
{
    ft::multimap<char, int> a;

    a.insert(ft::make_pair<char, int>('a', 5));
    assert(a.size() == 1);
    a.insert(ft::make_pair<char, int>('a', 5));
    assert(a.size() == 2);
    a.insert(ft::make_pair<char, int>('a', 999));
    assert(a.size() == 3);
    a.insert(ft::make_pair<char, int>('b', 0));
    assert(a.size() == 4);
}

static void test_insert_range_practical()
{
    ft::multimap<char, int> a;

    a.insert(ft::make_pair<char, int>('a', 5));
    a.insert(ft::make_pair<char, int>('b', 6));
    a.insert(ft::make_pair<char, int>('a', 5));
    a.insert(ft::make_pair<char, int>('b', 6));

    assert(a.size() == 4);

    ft::multimap<char, int> b;

    b.insert(a.begin(), a.end());

    assert(b.size() == 4);
    b.insert(a.begin(), a.end());
    assert(b.size() == 8);
}

static void test_insert_hint_practical()
{
    ft::multimap<char, int> a;

    a.insert(a.begin(), ft::make_pair<char, int>('a', 5));

    assert(a.size() == 1);
    a.insert(a.begin(), ft::make_pair<char, int>('a', 6));
    assert(a.size() == 2);

    a.insert(a.begin(), ft::make_pair<char, int>('b', 6));
    assert(a.size() == 3);
}

static void test_insert_practical()
{
    test_insert_single_practical();
    test_insert_range_practical();
    test_insert_hint_practical();
}

template <typename T1, typename T2>
static void test_insert()
{
    ft::multimap<T1, T2> a;
    ft::multimap<T1, T2> empty;

    a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    assert(a.size() == 1);
    a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    assert(a.size() == 2);

    ft::multimap<T1, T2> b;

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
    test_insert<char, int>();
    test_insert<int, int>();
    test_insert<float, char>();
    test_insert<char *, int>();
    test_insert<int, std::string>();

    display_success("insert");
}

static void test_erase_practical()
{
    ft::multimap<char, int> a;

    a.insert(a.begin(), ft::make_pair<char, int>('a', 1));
    a.insert(a.begin(), ft::make_pair<char, int>('b', 2));
    a.insert(a.begin(), ft::make_pair<char, int>('a', 3));
    a.insert(a.begin(), ft::make_pair<char, int>('b', 4));

    assert((*(a.begin())).first == 'a');
    assert(a.size() == 4);

    a.erase(a.begin());

    assert((*(a.begin())).first == 'a');
    assert((*(a.begin())).second == 3);
    assert(a.size() == 3);

    a.erase(a.begin());

    assert((*(a.begin())).first == 'b');
    assert((*(a.begin())).second == 2);
    assert(a.size() == 2);

    a.erase(a.begin());

    assert((*(a.begin())).first == 'b');
    assert((*(a.begin())).second == 4);

    assert(a.size() == 1);

    a.erase(a.begin());
    assert(a.empty());
}

template <typename T1, typename T2>
static void test_erase()
{
    ft::multimap<T1, T2> a;

    a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    a.erase(a.begin());

    assert(a.empty());
    a.erase(a.begin());
    a.erase(a.end());
    assert(a.empty());
}

static void test_erase_key_practical()
{
    ft::multimap<char, int> a;

    a.insert(a.begin(), ft::make_pair<char, int>('a', 1));
    a.insert(a.begin(), ft::make_pair<char, int>('a', 2));
    a.insert(a.begin(), ft::make_pair<char, int>('b', 3));
    a.insert(a.begin(), ft::make_pair<char, int>('b', 4));

    assert(a.erase('a') == 2);
    assert(a.erase('a') == 0);

    assert(a.erase('b') == 2);
    assert(a.erase('b') == 0);

    assert(a.erase('c') == 0);
    assert(a.erase('d') == 0);
    assert(a.erase('z') == 0);
    assert(a.empty());
}

template <typename T1, typename T2>
static void test_erase_key()
{
    ft::multimap<T1, T2> a;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    assert(a.erase(T1()) == 50);

    assert(a.empty());
    assert(a.erase(T1()) == 0);
    assert(a.empty());
}

static void test_erase_range_practical()
{
    ft::multimap<char, int> a;

    a.insert(a.begin(), ft::make_pair<char, int>('a', 1));
    a.insert(a.begin(), ft::make_pair<char, int>('b', 2));
    a.insert(a.begin(), ft::make_pair<char, int>('a', 5));
    a.insert(a.begin(), ft::make_pair<char, int>('c', 3));
    a.insert(a.begin(), ft::make_pair<char, int>('d', 4));

    a.erase(a.begin(), ++a.begin());
    assert(a.size() == 4);
    assert((*(a.begin())).first == 'a');
    assert((*(a.begin())).second == 5);

    a.erase(a.begin(), a.end());
    assert(a.empty());
}

template <typename T1, typename T2>
static void test_erase_range()
{
    ft::multimap<T1, T2> a;

    a.erase(a.begin(), a.end());
    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    a.erase(a.begin(), a.end());

    assert(a.empty());
}
static void erase()
{
    test_erase_practical();
    test_erase_range_practical();
    test_erase_key_practical();

    test_erase<char, int>();
    test_erase<int, int>();
    test_erase<float, char>();
    test_erase<char *, int>();
    test_erase<int, std::string>();

    test_erase_key<char, int>();
    test_erase_key<int, int>();
    test_erase_key<float, char>();
    test_erase_key<char *, int>();
    test_erase_key<int, std::string>();

    test_erase_range<char, int>();
    test_erase_range<int, int>();
    test_erase_range<float, char>();
    test_erase_range<char *, int>();
    test_erase_range<int, std::string>();

    display_success("erase");
}

static void test_swap_practical()
{
    ft::multimap<char, int> a;

    a.insert(a.begin(), ft::make_pair<char, int>('a', 1));
    a.insert(a.begin(), ft::make_pair<char, int>('b', 2));
    a.insert(a.begin(), ft::make_pair<char, int>('c', 3));
    a.insert(a.begin(), ft::make_pair<char, int>('d', 4));
    a.insert(a.begin(), ft::make_pair<char, int>('a', 6));

    ft::multimap<char, int> b;

    a.swap(b);

    assert(b.size() == 5);
    assert(a.empty());

    assert((*(b.begin())).first == 'a');
    assert((*(++b.begin())).first == 'a');
    assert((*(--b.end())).first == 'd');
}

template <typename T1, typename T2>
static void test_swap()
{
    ft::multimap<T1, T2> a;
    ft::multimap<T1, T2> b;

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    assert(a.size() == 50);
    assert((*(a.begin())).first == T1());
    assert((*(a.begin())).second == T2());
    assert((*(--a.end())).first == T1());
    assert((*(--a.end())).second == T2());
    assert(b.empty());

    a.swap(b);

    assert(b.size() == 50);
    assert((*(b.begin())).first == T1());
    assert((*(b.begin())).second == T2());
    assert((*(--b.end())).first == T1());
    assert((*(--b.end())).second == T2());
    assert(a.empty());
}

static void swap()
{
    test_swap_practical();
    test_swap<char, int>();
    test_swap<int, int>();
    test_swap<float, char>();
    test_swap<char *, int>();
    test_swap<int, std::string>();

    display_success("swap");
}

static void test_clear_practical()
{
    ft::multimap<char, int> a;

    a.clear();
    assert(a.empty());

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<char, int>(i, i));

    assert(a.size() == 50);

    a.clear();

    assert(a.empty());
}

template <typename T1, typename T2>
static void test_clear()
{
    ft::multimap<T1, T2> a;

    a.clear();

    a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    a.clear();
    assert(a.empty());

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    assert(a.size() == 50);

    a.clear();
    assert(a.empty());

    a.clear();
    assert(a.empty());
}

static void clear()
{
    test_clear_practical();
    test_clear<char, int>();
    test_clear<int, int>();
    test_clear<float, char>();
    test_clear<char *, int>();
    test_clear<int, std::string>();

    display_success("clear");
}

static void test_find_practical()
{
    ft::multimap<char, int> a;

    a.insert(ft::make_pair<char, int>('a', 1));
    a.insert(ft::make_pair<char, int>('a', 2));
    a.insert(ft::make_pair<char, int>('b', 4));

    assert(a.find('a')->first == 'a');

    a.clear();
    assert(a.empty());

    for (int i = 0; i < 50; i++)
    {
        assert(a.find(i) == a.end());
        a.insert(ft::make_pair<char, int>(i, i));
        assert(a.find(i) != a.end());
    }
}

template <typename T1, typename T2>
static void test_find()
{
    ft::multimap<T1, T2> a;

    assert(a.find(T1()) == a.end());

    for (int i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    assert(a.find(T1()) != a.end());

    const ft::multimap<T1, T2> b(a);

    assert(b.find(T1()) != b.end());
}

static void find()
{
    test_find_practical();
    test_find<char, int>();
    test_find<int, int>();
    test_find<float, char>();
    test_find<char *, int>();
    test_find<int, std::string>();

    display_success("find");
}

static void test_count_practical()
{
    ft::multimap<char, int> a;

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.count(i) == 0);
        a.insert(ft::make_pair<char, int>(i, i));
        assert(a.count(i) == 1);
    }

    a.clear();

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.count('a') == i);
        a.insert(ft::make_pair<char, int>('a', i));
    }
}

template <typename T1, typename T2>
static void test_count()
{
    ft::multimap<T1, T2> a;

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.count(T1()) == i);
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));
    }
}

static void count()
{
    test_count_practical();
    test_count<char, int>();
    test_count<int, int>();
    test_count<float, char>();
    test_count<char *, int>();
    test_count<int, std::string>();

    display_success("count");
}

static void test_lower_bound_practical()
{
    ft::multimap<char, int> a;

    a.insert(ft::make_pair<char, int>('a', 1));
    a.insert(ft::make_pair<char, int>('a', 2));
    a.insert(ft::make_pair<char, int>('b', 3));
    a.insert(ft::make_pair<char, int>('c', 4));

    assert(a.lower_bound('a') == a.begin());
    assert(a.lower_bound('c') == --a.end());
    assert(a.lower_bound('z') == a.end());
}

template <typename T1, typename T2>
static void test_lower_bound()
{
    ft::multimap<T1, T2> a;

    assert(a.lower_bound(T1()) == a.end());

    a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    assert(a.lower_bound(T1()) == a.begin());
    assert((*(a.lower_bound(T1()))).first == T1());
    assert((*(a.lower_bound(T1()))).second == T2());

    const ft::multimap<T1, T2> b(a);

    assert(b.lower_bound(T1()) == b.begin());
    assert((*(b.lower_bound(T1()))).first == T1());
    assert((*(b.lower_bound(T1()))).second == T2());
}

static void lower_bound()
{
    test_lower_bound_practical();
    test_lower_bound<char, int>();
    test_lower_bound<int, int>();
    test_lower_bound<float, char>();
    test_lower_bound<char *, int>();
    test_lower_bound<int, std::string>();

    display_success("lower_bound");
}

static void test_upper_bound_practical()
{
    ft::multimap<char, int> a;

    a.insert(ft::make_pair<char, int>('a', 1));
    a.insert(ft::make_pair<char, int>('a', 2));
    a.insert(ft::make_pair<char, int>('b', 3));
    a.insert(ft::make_pair<char, int>('c', 4));

    assert((*(a.upper_bound('a'))).first == 'b');
    assert(a.upper_bound('b') == --a.end());
    assert(a.upper_bound('c') == a.end());
}

template <typename T1, typename T2>
static void test_upper_bound()
{
    ft::multimap<T1, T2> a;

    assert(a.upper_bound(T1()) == a.end());

    for (size_t i = 0; i < 50; i++)
        a.insert(ft::make_pair<T1, T2>(T1(), T2()));

    assert(a.upper_bound(T1()) == a.end());

    const ft::multimap<T1, T2> b(a);

    assert(b.upper_bound(T1()) == b.end());
}

static void upper_bound()
{
    test_upper_bound_practical();
    test_upper_bound<char, int>();
    test_upper_bound<int, int>();
    test_upper_bound<float, char>();
    test_upper_bound<char *, int>();
    test_upper_bound<int, std::string>();

    display_success("upper_bound");
}

static void test_equal_range_practical()
{
    ft::multimap<char, int> mymm;

    mymm.insert(ft::Pair<char, int>('a', 10));
    mymm.insert(ft::Pair<char, int>('b', 20));
    mymm.insert(ft::Pair<char, int>('b', 30));
    mymm.insert(ft::Pair<char, int>('b', 40));
    mymm.insert(ft::Pair<char, int>('c', 50));
    mymm.insert(ft::Pair<char, int>('c', 60));
    mymm.insert(ft::Pair<char, int>('d', 60));

    assert(mymm.equal_range('a').first->first == 'a');
    assert(mymm.equal_range('a').second->first == 'b');

    assert(mymm.equal_range('b').first->second == 20);
    assert(mymm.equal_range('b').second->first == 'c');
    assert(mymm.equal_range('b').second->second == 50);

    assert(mymm.equal_range('c').first->second == 50);
    assert(mymm.equal_range('c').second->first == 'd');

    assert(mymm.equal_range('d').first->first == 'd');
    assert(mymm.equal_range('d').second == mymm.end());
}

static void equal_range()
{
    test_equal_range_practical();

    display_success("equal_range");
}

void test_multimap()
{
    display("          === multimap ===", COLOR_CYAN);

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

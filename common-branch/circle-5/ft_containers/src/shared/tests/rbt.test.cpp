/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:14:08 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:54:31 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../RedBlackTree.hpp"
#include "../../test-utils/testUtils.hpp"
#include "../../shared/Less.hpp"

template <typename T>
static bool equal(const T &a, const T &b)
{
    return a == b;
}

void displayElem(const int &e)
{
    std::cout << " - " << e;
}

bool isGreaterThanZero(const int &e)
{
    return e > 0;
}

template <typename T>
static void test_default_constructor()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    assert(tree.empty());

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    assert(tree.size() == 50);
    tree.erase(tree.begin());
    assert(tree.size() == 49);
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
static void test_range_constructor()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    ft::RedBlackTree<T, ft::Less<T>, true> tree_copy(tree.begin(), tree.end());

    assert(tree_copy.size() == 50);

    tree_copy.insert(T());

    assert(tree.size() == 50);
    assert(tree_copy.size() == 51);

    tree_copy.erase(tree_copy.begin());
    assert(tree_copy.size() == 50);
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
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    ft::RedBlackTree<T, ft::Less<T>, true> tree_copy(tree);

    assert(tree.size() == 50);
    assert(tree_copy.size() == 50);

    tree_copy.insert(T());

    assert(tree.size() == 50);
    assert(tree_copy.size() == 51);

    tree_copy.erase(tree_copy.begin());
    assert(tree_copy.size() == 50);
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
    ft::RedBlackTree<T, ft::Less<T>, true> tree;
    ft::RedBlackTree<T, ft::Less<T>, true> tree_copy;

    tree_copy = tree;

    assert(tree.empty());
    assert(tree_copy.empty());

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    tree_copy = tree;

    assert(tree.size() == 50);
    assert(tree_copy.size() == 50);
    tree.erase(tree.begin());
    assert(tree.size() == 49);
    assert(tree_copy.size() == 50);

    tree_copy.insert(T());
    assert(tree.size() == 49);
    assert(tree_copy.size() == 51);
}

static void assignement_operator()
{
    test_assignement_operator<int>();
    test_assignement_operator<float>();
    test_assignement_operator<char>();
    test_assignement_operator<char *>();
    test_assignement_operator<std::string>();

    display_success("assignement operator");
}

template <typename T>
static void test_empty()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    assert(tree.empty());

    tree.insert(T());
    assert(!tree.empty());

    tree.erase(tree.begin());
    assert(tree.empty());
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
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    assert(tree.size() == 0);

    for (int i = 0; i < 50; i++)
        tree.insert(T());
    assert(tree.size() == 50);

    tree.erase(tree.begin());

    assert(tree.size() == 49);
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

template <typename T>
static void test_insert_range()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;
    ft::RedBlackTree<T, ft::Less<T>, true> tree_copy;

    for (int i = 0; i < 50; i++)
        tree.insert(T());
    assert(tree.size() == 50);

    tree_copy.insert(tree.begin(), tree.end());
    assert(tree_copy.size() == 50);

    tree_copy.insert(tree.begin(), tree.end());
    assert(tree_copy.size() == 100);

    tree_copy.erase(tree_copy.begin());
    assert(tree_copy.size() == 99);
}

template <typename T>
static void test_insert()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    for (int i = 0; i < 50; i++)
        tree.insert(T());
    assert(tree.size() == 50);

    tree.erase(tree.begin());
    assert(tree.size() == 49);

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    assert(tree.size() == 99);
}

static void insert()
{
    test_insert<int>();
    test_insert<float>();
    test_insert<char>();
    test_insert<char *>();
    test_insert<std::string>();
    test_insert_range<int>();
    test_insert_range<float>();
    test_insert_range<char>();
    test_insert_range<char *>();
    test_insert_range<std::string>();

    display_success("insert");
}

template <typename T>
static void test_erase_range()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    tree.erase(tree.begin(), tree.end());

    assert(tree.empty());
}

template <typename T>
static void test_erase()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    for (int i = 0; i < 50; i++)
        tree.erase(tree.begin());

    assert(tree.empty());

    tree.erase(tree.begin());
    tree.erase(tree.end());

    assert(tree.empty());
}

static void erase()
{
    test_erase<int>();
    test_erase<float>();
    test_erase<char>();
    test_erase<char *>();
    test_erase<std::string>();

    test_erase_range<int>();
    test_erase_range<float>();
    test_erase_range<char>();
    test_erase_range<char *>();
    test_erase_range<std::string>();

    display_success("erase");
}

template <typename T>
static void test_erase_if_no_duplicates()
{
    ft::RedBlackTree<T, ft::Less<T>, false> tree;
    for (int i = 0; i < 50; i++)
        tree.insert(T());

    assert(tree.size() == 1);

    assert(tree.eraseIf(equal<T>, T()) == 1);
    assert(tree.empty());

    assert(tree.eraseIf(equal<T>, T()) == 0);
    assert(tree.empty());
}

template <typename T>
static void test_erase_if()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;
    for (int i = 0; i < 50; i++)
        tree.insert(T());

    assert(tree.eraseIf(equal<T>, T()) == 50);
    assert(tree.empty());

    assert(tree.eraseIf(equal<T>, T()) == 0);
    assert(tree.empty());
}

static void erase_if()
{
    test_erase_if<int>();
    test_erase_if<float>();
    test_erase_if<char>();
    test_erase_if<char *>();
    test_erase_if<std::string>();

    test_erase_if_no_duplicates<int>();
    test_erase_if_no_duplicates<float>();
    test_erase_if_no_duplicates<char>();
    test_erase_if_no_duplicates<char *>();
    test_erase_if_no_duplicates<std::string>();

    display_success("eraseIf");
}

static void test_begin_practical()
{
    ft::RedBlackTree<int, ft::Less<int>, true> tree;

    tree.insert(5);
    tree.insert(6);

    assert(*(tree.begin()) == 5);
    assert(*(++tree.begin()) == 6);
}

static void test_end_practical()
{
    ft::RedBlackTree<int, ft::Less<int>, true> tree;

    tree.insert(5);
    tree.insert(6);

    assert(*(++tree.end()) == 5);
    assert(*(--tree.end()) == 6);

    tree.clear();

    for (int i = 0; i < 50; i++)
        tree.insert(i);

    int i = 0;
    int count = 0;
    for (ft::RedBlackTree<int, ft::Less<int>, true>::iterator it = tree.begin(); it != tree.end(); it++)
    {
        assert(*it == i);
        i++;
        count++;
    }
    assert(count == 50);

    i = 49;
    count = 0;

    for (ft::RedBlackTree<int, ft::Less<int>, true>::iterator it = --tree.end(); it != --tree.begin(); it--)
    {
        assert(*it == i);
        i--;
        count++;
    }
    assert(count == 50);
}

template <typename T>
static void test_begin_end()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    int count = 0;
    for (typename ft::RedBlackTree<T, ft::Less<T>, true>::iterator it = tree.begin(); it != tree.end(); it++)
    {
        assert(*it == T());
        count++;
    }
    assert(count == 50);

    count = 0;
    for (typename ft::RedBlackTree<T, ft::Less<T>, true>::iterator it = --tree.end(); it != --tree.begin(); it--)
    {
        assert(*it == T());
        count++;
    }
    assert(count == 50);
}

static void begin_end()
{
    test_begin_practical();
    test_end_practical();
    test_begin_end<int>();
    test_begin_end<float>();
    test_begin_end<char>();
    test_begin_end<char *>();
    test_begin_end<std::string>();

    display_success("begin and end");
}

template <typename T>
static void test_rbegin_rend()
{

    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    int count = 0;
    for (typename ft::RedBlackTree<T, ft::Less<T>, true>::reverse_iterator it = tree.rbegin(); it != tree.rend(); it++)
    {
        count++;
    }

    assert(count == 50);
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
static void test_swap()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;
    ft::RedBlackTree<T, ft::Less<T>, true> tree_copy;

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    tree.swap(tree_copy);

    assert(tree.empty());
    assert(tree_copy.size() == 50);

    tree.insert(T());
    assert(tree.size() == 1);
    tree.erase(tree.begin());
    assert(tree.empty());

    tree_copy.insert(T());
    assert(tree_copy.size() == 51);
    for (int i = 0; i < 51; i++)
        tree_copy.erase(tree_copy.begin());

    assert(tree_copy.empty());
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

static void test_find_practical()
{
    ft::RedBlackTree<int, ft::Less<int>, true> tree;

    assert(tree.find(equal<int>, int()) == tree.end());

    for (int i = 0; i < 50; i++)
        tree.insert(i);

    const ft::RedBlackTree<int, ft::Less<int>, true> tree_const(tree);

    assert(tree.find(equal<int>, 0) == tree.begin());
    assert(tree.find(equal<int>, 1) == ++tree.begin());
    assert(tree.find(equal<int>, 49) == --tree.end());

    assert(tree_const.find(equal<int>, 0) == tree_const.begin());
    assert(tree_const.find(equal<int>, 1) == ++tree_const.begin());
    assert(tree_const.find(equal<int>, 49) == --tree_const.end());
}

template <typename T>
static void test_find()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    assert(tree.find(equal<T>, T()) == tree.end());

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    assert(tree.find(equal<T>, T()) != tree.end());
}

static void find()
{
    test_find_practical();
    test_find<int>();
    test_find<float>();
    test_find<char>();
    test_find<char *>();
    test_find<std::string>();

    display_success("find");
}

template <typename T>
static void test_clear()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    tree.clear();

    assert(tree.empty());

    tree.insert(T());
    assert(tree.size() == 1);

    tree.clear();
    assert(tree.empty());
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
static void test_count_if()
{
    ft::RedBlackTree<T, ft::Less<T>, true> tree;

    assert(tree.countIf(equal<T>, T()) == 0);

    for (int i = 0; i < 50; i++)
        tree.insert(T());

    assert(tree.countIf(equal<T>, T()) == 50);

    ft::RedBlackTree<T, ft::Less<T>, false> tree_no_duplicates;

    assert(tree_no_duplicates.countIf(equal<T>, T()) == 0);

    for (int i = 0; i < 50; i++)
        tree_no_duplicates.insert(T());

    assert(tree_no_duplicates.countIf(equal<T>, T()) == 1);
}

static void count_if()
{
    test_count_if<int>();
    test_count_if<float>();
    test_count_if<char>();
    test_count_if<char *>();
    test_count_if<std::string>();

    display_success("count if");
}

void test_red_black_tree()
{

    display("          === red black tree ===", COLOR_CYAN);

    default_constructor();
    range_constructor();
    copy_constructor();
    assignement_operator();

    display("    === Iterators ===", COLOR_YELLOW);
    begin_end();
    rbegin_rend();

    display("    === Capacity ===", COLOR_YELLOW);

    empty();
    size();

    insert();
    erase();
    erase_if();
    swap();
    clear();
    find();
    count_if();

    display_success("Red Black Tree");
}

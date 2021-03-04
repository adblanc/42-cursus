/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 17:35:21 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:08:32 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Queue.hpp"
#include "../../test-utils/testUtils.hpp"

template <typename T>
static void test_default_constructor()
{
    ft::queue<T> a;
    std::queue<T> b;

    assert(a.empty());
    assert(b.empty());

    a.push(T());
    b.push(T());

    assert(a.size());
    assert(b.size());

    a.pop();
    b.pop();

    assert(a.empty());
    assert(b.empty());
}

static void default_constuctor()
{
    test_default_constructor<int>();
    test_default_constructor<float>();
    test_default_constructor<char>();
    test_default_constructor<char *>();
    test_default_constructor<std::string>();

    display_success("default_constructor");
}

template <typename T>
static void test_empty()
{
    ft::queue<T> a;
    std::queue<T> b;

    assert(a.empty());
    assert(b.empty());

    a.push(T());
    b.push(T());

    assert(!a.empty());
    assert(!b.empty());

    a.pop();
    b.pop();

    assert(a.empty());
    assert(b.empty());
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
    ft::queue<T> a;
    std::queue<T> b;

    assert(a.empty());
    assert(b.empty());

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.size() == i);
        assert(b.size() == i);
        a.push(T());
        b.push(T());
    }

    assert(a.size() == 50);
    assert(b.size() == 50);

    a.pop();
    b.pop();

    assert(a.size() == 49);
    assert(b.size() == 49);
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

static void test_front_practical()
{
    ft::queue<int> a;
    std::queue<int> b;

    a.push(0);
    b.push(0);

    for (int i = 1; i < 50; i++)
    {
        a.push(i);
        b.push(i);
        assert(a.front() == 0);
        assert(b.front() == 0);
    }
}

template <typename T>
static void test_front()
{
    ft::queue<T> a;
    std::queue<T> b;

    a.push(T());
    b.push(T());

    assert(a.front() == T());
    assert(b.front() == T());
}

static void front()
{
    test_front_practical();
    test_front<int>();
    test_front<float>();
    test_front<char>();
    test_front<char *>();
    test_front<std::string>();

    display_success("front");
}

static void test_back_practical()
{
    ft::queue<int> a;
    std::queue<int> b;

    for (int i = 0; i < 50; i++)
    {
        a.push(i);
        b.push(i);
        assert(a.back() == i);
        assert(b.back() == i);
    }
}

template <typename T>
static void test_back()
{
    ft::queue<T> a;
    std::queue<T> b;

    a.push(T());
    b.push(T());

    assert(a.back() == T());
    assert(b.back() == T());
}

static void back()
{
    test_back_practical();
    test_back<int>();
    test_back<float>();
    test_back<char>();
    test_back<char *>();
    test_back<std::string>();

    display_success("back");
}

template <typename T>
static void test_push()
{
    ft::queue<T> a;
    std::queue<T> b;

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.size() == i);
        assert(b.size() == i);
        a.push(T());
        b.push(T());
    }

    a.pop();
    assert(a.size() == 49);
    a.push(T());
    assert(a.size() == 50);

    b.pop();
    assert(b.size() == 49);
    b.push(T());
    assert(b.size() == 50);
}

static void push()
{
    test_push<int>();
    test_push<float>();
    test_push<char>();
    test_push<char *>();
    test_push<std::string>();

    display_success("push");
}

template <typename T>
static void test_pop()
{
    ft::queue<T> a;
    std::queue<T> b;

    for (size_t i = 0; i < 50; i++)
    {
        a.push(T());
        b.push(T());
    }

    for (size_t i = 0; i < 50; i++)
    {
        assert(a.size() == 50 - i);
        assert(b.size() == 50 - i);
        a.pop();
        b.pop();
    }
    assert(a.empty());
    assert(b.empty());
}

static void test_pop_practical()
{
    ft::queue<int> a;
    std::queue<int> b;
    for (int i = 0; i < 50; i++)
    {
        a.push(i);
        b.push(i);
    }

    for (int i = 0; i < 50; i++)
    {
        assert(a.size() == (size_t)(50 - i));
        assert(b.size() == (size_t)(50 - i));
        assert(a.front() == b.front());
        assert(a.back() == b.back());
        a.pop();
        b.pop();
    }
}

static void pop()
{
    test_pop_practical();
    test_pop<int>();
    test_pop<float>();
    test_pop<char>();
    test_pop<char *>();
    test_pop<std::string>();

    display_success("pop");
}

static void test_relational_operators_practical()
{
    ft::queue<int> foo;
    ft::queue<int> bar;

    foo.push(0);
    bar.push(1);

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
    ft::queue<T> foo;
    ft::queue<T> bar;

    foo.push(T());

    assert(foo > bar);
    assert(foo >= bar);
    assert(!(foo < bar));
    assert(!(foo <= bar));
    assert(bar < foo);
    assert(bar <= foo);
    assert(bar != foo);
    assert(foo != bar);
    assert(bar == bar);
    assert(foo == foo);
}

static void relational_operators()
{
    test_relational_operators_practical();
    test_relational_operators<int>();

    display_success("relational operators");
}

void test_queue()
{
    display("          === queue ===", COLOR_CYAN);

    display("      === Member functions ===", COLOR_RED);
    default_constuctor();
    empty();
    size();
    front();
    back();
    push();
    pop();
    display("      === Non-member function overloads ===", COLOR_RED);
    relational_operators();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 17:35:21 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:08:59 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Stack.hpp"
#include "../../test-utils/testUtils.hpp"

template <typename T>
static void test_default_constructor()
{
    ft::stack<T> a;
    std::stack<T> b;

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
    ft::stack<T> a;
    std::stack<T> b;

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
    ft::stack<T> a;
    std::stack<T> b;

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

static void test_top_practical()
{
    ft::stack<int> a;
    std::stack<int> b;

    for (int i = 0; i < 50; i++)
    {
        a.push(i);
        b.push(i);
        assert(a.top() == i);
        assert(b.top() == i);
    }
}

template <typename T>
static void test_top()
{
    ft::stack<T> a;
    std::stack<T> b;

    a.push(T());
    b.push(T());

    assert(a.top() == T());
    assert(b.top() == T());
}

static void top()
{
    test_top_practical();
    test_top<int>();
    test_top<float>();
    test_top<char>();
    test_top<char *>();
    test_top<std::string>();

    display_success("top");
}

template <typename T>
static void test_push()
{
    ft::stack<T> a;
    std::stack<T> b;

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
    ft::stack<T> a;
    std::stack<T> b;

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

static void pop()
{
    test_pop<int>();
    test_pop<float>();
    test_pop<char>();
    test_pop<char *>();
    test_pop<std::string>();

    display_success("pop");
}

static void test_relational_operators_practical()
{
    ft::stack<int> foo;
    ft::stack<int> bar;

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
    ft::stack<T> foo;
    ft::stack<T> bar;

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

void test_stack()
{
    display("          === stack ===", COLOR_CYAN);

    display("      === Member functions ===", COLOR_RED);
    default_constuctor();
    empty();
    size();
    top();
    push();
    pop();
    display("      === Non-member function overloads ===", COLOR_RED);
    relational_operators();
}

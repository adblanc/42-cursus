/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 17:22:48 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:09:51 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/Vector.hpp"
#include <cstddef>

namespace ft
{

template <typename T, class Container = ft::vector<T> >
class stack
{
public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

    explicit stack(const container_type &ctnr = container_type());
    ~stack();

    bool empty() const;
    size_type size() const;

    value_type &top();
    const value_type &top() const;

    void push(const value_type &val);
    void pop();

private:
    stack(const stack &src);
    stack &operator=(const stack &rhs);

    template <typename Type, class Cont>
    friend bool operator<(const stack<Type, Cont> &lhs, const stack<Type, Cont> &rhs);

    container_type container;
};

template <typename T, class Container>
stack<T, Container>::stack(const container_type &ctnr) : container(ctnr)
{
}

template <typename T, class Container>
stack<T, Container>::~stack()
{
}

template <typename T, class Container>
bool stack<T, Container>::empty() const
{
    return container.empty();
}

template <typename T, class Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const
{
    return container.size();
}

template <typename T, class Container>
typename stack<T, Container>::value_type &stack<T, Container>::top()
{
    return container.back();
}

template <typename T, class Container>
const typename stack<T, Container>::value_type &stack<T, Container>::top() const
{
    return container.back();
}

template <typename T, class Container>
void stack<T, Container>::push(const value_type &val)
{
    return container.push_back(val);
}

template <typename T, class Container>
void stack<T, Container>::pop()
{
    return container.pop_back();
}

// Non-member function overloads
// Relational operators
template <typename T, class Container>
bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return !(lhs < rhs || lhs > rhs);
}

template <typename T, class Container>
bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return !(lhs == rhs);
}
template <typename T, class Container>
bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return lhs.container < rhs.container;
}
template <typename T, class Container>
bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return !(lhs > rhs);
}
template <typename T, class Container>
bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return (rhs < lhs);
}
template <typename T, class Container>
bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return !(lhs < rhs);
}

} // namespace ft

#endif

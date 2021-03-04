/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 18:26:27 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:10:01 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../list/List.hpp"
#include <cstddef>

namespace ft
{

    template <typename T, class Container = ft::list<T> >
    class queue
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

        explicit queue(const container_type &ctnr = container_type());
        ~queue();

        bool empty() const;
        size_type size() const;

        value_type &front();
        const value_type &front() const;

        value_type &back();
        const value_type &back() const;

        void push(const value_type &val);
        void pop();

    private:
        queue(const queue &src);
        queue &operator=(const queue &rhs);

        template <typename Type, class Cont>
        friend bool operator<(const queue<Type, Cont> &lhs, const queue<Type, Cont> &rhs);

        container_type container;
    };

    template <typename T, class Container>
    queue<T, Container>::queue(const container_type &ctnr) : container(ctnr)
    {
    }

    template <typename T, class Container>
    queue<T, Container>::~queue()
    {
    }

    template <typename T, class Container>
    bool queue<T, Container>::empty() const
    {
        return container.empty();
    }

    template <typename T, class Container>
    typename queue<T, Container>::size_type queue<T, Container>::size() const
    {
        return container.size();
    }

    template <typename T, class Container>
    typename queue<T, Container>::value_type &queue<T, Container>::front()
    {
        return container.front();
    }

    template <typename T, class Container>
    const typename queue<T, Container>::value_type &queue<T, Container>::front() const
    {
        return container.front();
    }

    template <typename T, class Container>
    typename queue<T, Container>::value_type &queue<T, Container>::back()
    {
        return container.back();
    }

    template <typename T, class Container>
    const typename queue<T, Container>::value_type &queue<T, Container>::back() const
    {
        return container.back();
    }

    template <typename T, class Container>
    void queue<T, Container>::push(const value_type &val)
    {
        return container.push_back(val);
    }

    template <typename T, class Container>
    void queue<T, Container>::pop()
    {
        return container.pop_front();
    }

    // Non-member function overloads
    // Relational operators
    template <typename T, class Container>
    bool operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
    {
        return !(lhs < rhs || lhs > rhs);
    }

    template <typename T, class Container>
    bool operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
    {
        return !(lhs == rhs);
    }
    template <typename T, class Container>
    bool operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
    {
        return lhs.container < rhs.container;
    }
    template <typename T, class Container>
    bool operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
    {
        return !(lhs > rhs);
    }
    template <typename T, class Container>
    bool operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
    {
        return (rhs < lhs);
    }
    template <typename T, class Container>
    bool operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
    {
        return !(lhs < rhs);
    }

} // namespace ft

#endif

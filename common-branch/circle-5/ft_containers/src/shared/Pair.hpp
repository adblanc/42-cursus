/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:34:11 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:05:58 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{

    template <class T1, class T2>
    struct Pair
    {
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        Pair() : first(T1()), second(T2()){};
        template <class U, class V>
        Pair(const Pair<U, V> &pr) : first(pr.first), second(pr.second){};
        Pair(const first_type &a, const second_type &b) : first(a), second(b){};
    };

    template <class T1, class T2>
    Pair<T1, T2> make_pair(T1 t, T2 u)
    {
        return Pair<T1, T2>(t, u);
    }

    template <class T1, class T2>
    bool operator==(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class T1, class T2>
    bool operator!=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
    {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }
} // namespace ft

#endif

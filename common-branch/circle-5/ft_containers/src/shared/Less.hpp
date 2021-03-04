/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 19:21:45 by adrien            #+#    #+#             */
/*   Updated: 2020/04/14 19:29:26 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
#define LESS_HPP

#include "./BinaryFunction.hpp"

// http://www.cplusplus.com/reference/functional/less/

namespace ft
{

template <class T>
struct Less : public ft::BinaryFunction<T, T, bool>
{
    bool operator()(const T &x, const T &y) const;
};

template <class T>
bool Less<T>::operator()(const T &x, const T &y) const
{
    return x < y;
}

}; // namespace ft

#endif
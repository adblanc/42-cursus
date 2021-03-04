/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryFunction.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 19:24:14 by adrien            #+#    #+#             */
/*   Updated: 2020/04/14 19:29:09 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYFUNCTION_HPP
#define BINARYFUNCTION_HPP

// http://www.cplusplus.com/reference/functional/binary_function/

namespace ft
{

template <class Arg1, class Arg2, class Result>
struct BinaryFunction
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};
} // namespace ft

#endif
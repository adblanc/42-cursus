/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:21:01 by adrien            #+#    #+#             */
/*   Updated: 2020/03/11 10:52:10 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

class Span
{
public:
    Span(void);
    Span(unsigned int N);
    Span(const Span &src);
    ~Span();

    Span &operator=(const Span &rhs);

    void addNumber(int);
    void addNumber(std::vector<int>::iterator start, std::vector<int>::iterator end);

    int shortestSpan(void);
    int longestSpan(void);

private:
    std::vector<int> cont;
    unsigned int limit;
};

#endif

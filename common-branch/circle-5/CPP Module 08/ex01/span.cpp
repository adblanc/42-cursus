/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:20:59 by adrien            #+#    #+#             */
/*   Updated: 2020/03/11 10:53:59 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

Span::Span(void)
{
    this->limit = 10;
};

Span::Span(unsigned int N)
{
    this->limit = N;
}

Span::Span(const Span &src)
{
    *this = src;
};

Span::~Span(){

};

Span &Span::operator=(const Span &rhs)
{
    if (this != &rhs)
    {
        this->limit = rhs.limit;
    }
    return (*this);
};

void Span::addNumber(int n)
{
    if (this->cont.size() >= this->limit)
        throw std::length_error("Container is at its limit. Cannot add any more number.");

    this->cont.push_back(n);
}

void Span::addNumber(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    for (std::vector<int>::iterator it = start; it != end; it++)
        this->addNumber(*it);
}

int Span::shortestSpan(void)
{
    if (this->cont.size() <= 1)
        throw std::length_error("Container does not contain enough numbers to get a span out of it.");

    std::vector<int>::iterator minIt = std::min_element(this->cont.begin(), this->cont.end());

    int minLeft = *std::min_element(this->cont.begin(), minIt);
    int minRight = *std::min_element(minIt + 1, this->cont.end());

    int minTwo = (minIt != this->cont.begin() && minLeft < minRight) ? minLeft : minRight;

    return (*minIt > minTwo ? *minIt - minTwo : minTwo - *minIt);
}

int Span::longestSpan(void)
{
    if (this->cont.size() <= 1)
        throw std::length_error("Container does not contain enough numbers to get a span out of it.");

    int max = *std::max_element(this->cont.begin(), this->cont.end());
    int min = *std::min_element(this->cont.begin(), this->cont.end());

    return (max - min);
}

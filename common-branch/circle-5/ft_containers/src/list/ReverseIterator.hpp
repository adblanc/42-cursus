/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:29:56 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:50:03 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

template <class Iterator>
class ReverseIterator
{
public:
    typedef Iterator iterator_type;
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;

    explicit ReverseIterator(iterator_type it);
    template <class Iter>
    ReverseIterator(const ReverseIterator<Iter> &rev_it);
    ReverseIterator(void);
    ~ReverseIterator();

    ReverseIterator &operator=(const ReverseIterator &rhs);

    iterator_type base() const;

    reference operator*() const;
    ReverseIterator &operator++();
    ReverseIterator operator++(int);
    ReverseIterator &operator--();
    ReverseIterator operator--(int);
    pointer operator->() const;

private:
    iterator_type it;
};

template <class Iterator>
ReverseIterator<Iterator>::ReverseIterator() : it()
{
}

template <class Iterator>
ReverseIterator<Iterator>::ReverseIterator(iterator_type it) : it(it)
{
}

template <class Iterator>
template <class Iter>
ReverseIterator<Iterator>::ReverseIterator(const ReverseIterator<Iter> &rev_it) : it(rev_it.it)
{
}

template <class Iterator>
ReverseIterator<Iterator>::~ReverseIterator()
{
}

template <class Iterator>
typename ReverseIterator<Iterator>::iterator_type ReverseIterator<Iterator>::base() const
{
    return it;
}

template <class Iterator>
ReverseIterator<Iterator>	&ReverseIterator<Iterator>::operator=(const ReverseIterator &rhs)
{
    if (this != &rhs)
    {
        this->it = rhs.it;
    }
    return (*this);
};

template <class Iterator>
typename ReverseIterator<Iterator>::reference	ReverseIterator<Iterator>::operator*() const
{
    Iterator itCopy(this->it);

    itCopy--;
    return (*itCopy);
}

template <class Iterator>
typename ReverseIterator<Iterator>::pointer ReverseIterator<Iterator>::operator->() const
{
    Iterator itCopy(this->it);

    itCopy--;
    return (itCopy.operator->());
}

template <class Iterator>
ReverseIterator<Iterator>	&ReverseIterator<Iterator>::operator++()
{
    it--;
    return (*this);
}

template <class Iterator>
ReverseIterator<Iterator> ReverseIterator<Iterator>::operator++(int)
{
    ReverseIterator tmp(*this);

    ++(*this);
    return (tmp);
}

template <class Iterator>
ReverseIterator<Iterator>	&ReverseIterator<Iterator>::operator--()
{
    it++;
    return (*this);
}

template <class Iterator>
ReverseIterator<Iterator> ReverseIterator<Iterator>::operator--(int)
{
    ReverseIterator tmp(*this);

    --(*this);
    return (tmp);
}

template <class Iterator>
bool operator==(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs)
{
    return lhs.base() == rhs.base();
}
template <class Iterator>
bool operator!=(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs)
{
    return lhs.base() != rhs.base();
}

#endif

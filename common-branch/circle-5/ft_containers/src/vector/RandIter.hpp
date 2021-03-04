/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandIter.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 15:22:46 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 13:25:37 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAND_ITER_HPP
#define RAND_ITER_HPP

#include "../shared/IteratorTypes.hpp"

template <typename T>
class RandIter
{
public:
    RandIter(void);
    RandIter(T *ptr);
    RandIter(const RandIter &src);
    ~RandIter();
    RandIter &operator=(const RandIter &rhs);

    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
    typedef ft::random_access_iterator_tag iterator_category;

    reference operator*(void) const;
    pointer operator->(void) const;
    RandIter &operator++();
    RandIter &operator--();
    RandIter operator++(int dummy);
    RandIter operator--(int dummy);
    RandIter &operator+=(const difference_type &offset);
    RandIter &operator-=(const difference_type &offset);
    RandIter operator+(difference_type offset) const;
    RandIter operator-(difference_type offset) const;

    bool operator==(const RandIter &rhs) const;
    bool operator!=(const RandIter &rhs) const;

    pointer ptr;

private:
};

template <typename T>
RandIter<T>::RandIter(void)
{
    ptr = NULL;
};

template <typename T>
RandIter<T>::RandIter(T *ptr)
{
    this->ptr = ptr;
};

template <typename T>
RandIter<T>::RandIter(const RandIter &src)
{
    *this = src;
};

template <typename T>
RandIter<T>::~RandIter(){

};

template <typename T>
RandIter<T> &RandIter<T>::operator=(const RandIter &rhs)
{
    if (this != &rhs)
    {
        this->ptr = rhs.ptr;
    }
    return (*this);
};

template <typename T>
typename RandIter<T>::reference RandIter<T>::operator*(void) const
{
    return *(this->ptr);
}

template <typename T>
typename RandIter<T>::pointer RandIter<T>::operator->(void) const
{
    return this->ptr;
}

template <typename T>
RandIter<T> &RandIter<T>::operator++()
{
    ptr++;
    return (*this);
}

template <typename T>
RandIter<T> &RandIter<T>::operator--()
{
    ptr--;
    return (*this);
}

template <typename T>
RandIter<T> RandIter<T>::operator++(int dummy)
{
    (void)dummy;
    RandIter<T> copy = *this;
    this->ptr++;
    return (copy);
}

template <typename T>
RandIter<T> RandIter<T>::operator--(int dummy)
{
    (void)dummy;
    RandIter<T> copy = *this;
    this->ptr--;
    return (copy);
}

template <typename T>
bool RandIter<T>::operator==(const RandIter &rhs) const
{
    return this->ptr == rhs.ptr;
}

template <typename T>
bool RandIter<T>::operator!=(const RandIter &rhs) const
{
    return this->ptr != rhs.ptr;
}

template <typename T>
RandIter<T> &RandIter<T>::operator+=(const difference_type &offset)
{
    this->ptr += offset;
    return (*this);
}

template <typename T>
RandIter<T> &RandIter<T>::operator-=(const difference_type &offset)
{
    this->ptr -= offset;
    return (*this);
}

template <typename T>
RandIter<T> RandIter<T>::operator+(difference_type offset) const
{
    RandIter copy(*this);

    copy.ptr += offset;

    return (copy);
}

template <typename T>
RandIter<T> RandIter<T>::operator-(difference_type offset) const
{
    RandIter copy(*this);

    copy.ptr -= offset;

    return (copy);
}

template <typename T>
typename RandIter<T>::difference_type operator-(const RandIter<T> &lhs, const RandIter<T> &rhs)
{
    return lhs.ptr - rhs.ptr;
}

template <typename T>
bool operator<(const RandIter<T> &lhs, const RandIter<T> &rhs)
{
    return lhs.ptr < rhs.ptr;
}

template <typename T>
bool operator<=(const RandIter<T> &lhs, const RandIter<T> &rhs)
{
    return lhs.ptr <= rhs.ptr;
}

template <typename T>
bool operator>(const RandIter<T> &lhs, const RandIter<T> &rhs)
{
    return lhs.ptr > rhs.ptr;
}
template <typename T>
bool operator>=(const RandIter<T> &lhs, const RandIter<T> &rhs)
{
    return lhs.ptr >= rhs.ptr;
}

template <typename T>
bool operator==(const RandIter<T> &lhs, const RandIter<T> &rhs)
{
    return lhs.ptr == rhs.ptr;
}

template <typename T>
bool operator!=(const RandIter<T> &lhs, const RandIter<T> &rhs)
{
    return lhs.ptr != rhs.ptr;
}

#endif

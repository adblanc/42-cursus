/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseRandIter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:06:53 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/24 15:52:23 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_RAND_DIR_ITERATOR_HPP
#define REV_RAND_DIR_ITERATOR_HPP

template <class Iterator>
class ReverseRandIter
{
public:
    typedef Iterator iterator_type;
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;

    explicit ReverseRandIter(iterator_type it);
    template <class Iter>
    ReverseRandIter(const ReverseRandIter<Iter> &rev_it);
    ReverseRandIter(void);
    ~ReverseRandIter();

    ReverseRandIter &operator=(const ReverseRandIter &rhs);

    iterator_type base() const;

    reference operator*() const;
    ReverseRandIter &operator++();
    ReverseRandIter operator++(int);
    ReverseRandIter &operator--();
    ReverseRandIter operator--(int);
    ReverseRandIter operator+(difference_type n) const;
    ReverseRandIter &operator+=(difference_type n);
    ReverseRandIter operator-(difference_type n) const;
    ReverseRandIter &operator-=(difference_type n);
    reference operator[](difference_type n) const;

    pointer operator->() const;

private:
    iterator_type it;
};

template <class Iterator>
ReverseRandIter<Iterator>::ReverseRandIter() : it()
{
}

template <class Iterator>
ReverseRandIter<Iterator>::ReverseRandIter(iterator_type it) : it(it)
{
}

template <class Iterator>
template <class Iter>
ReverseRandIter<Iterator>::ReverseRandIter(const ReverseRandIter<Iter> &rev_it) : it(rev_it.it)
{
}

template <class Iterator>
ReverseRandIter<Iterator>::~ReverseRandIter()
{
}

template <class Iterator>
typename ReverseRandIter<Iterator>::iterator_type ReverseRandIter<Iterator>::base() const
{
    return it;
}

template <class Iterator>
ReverseRandIter<Iterator>	&ReverseRandIter<Iterator>::operator=(const ReverseRandIter &rhs)
{
    if (this != &rhs)
    {
        this->it = rhs.it;
    }
    return (*this);
};

template <class Iterator>
typename ReverseRandIter<Iterator>::reference ReverseRandIter<Iterator>::operator*() const
{
    Iterator itCopy(this->it);

    itCopy--;
    return (*itCopy);
}

template <class Iterator>
typename ReverseRandIter<Iterator>::pointer ReverseRandIter<Iterator>::operator->() const
{
    Iterator itCopy(this->it);

    itCopy--;
    return (itCopy.operator->());
}

template <class Iterator>
ReverseRandIter<Iterator>	&ReverseRandIter<Iterator>::operator++()
{
    it--;
    return (*this);
}

template <class Iterator>
ReverseRandIter<Iterator>	ReverseRandIter<Iterator>::operator++(int)
{
    ReverseRandIter tmp(*this);

    ++(*this);
    return (tmp);
}

template <class Iterator>
ReverseRandIter<Iterator>	&ReverseRandIter<Iterator>::operator--()
{
    it++;
    return (*this);
}

template <class Iterator>
ReverseRandIter<Iterator>	ReverseRandIter<Iterator>::operator--(int)
{
    ReverseRandIter tmp(*this);

    --(*this);
    return (tmp);
}

template <class Iterator>
ReverseRandIter<Iterator>	ReverseRandIter<Iterator>::operator+(difference_type n) const
{
    return (ReverseRandIter<Iterator>(it - n));
}

template <class Iterator>
ReverseRandIter<Iterator>	&ReverseRandIter<Iterator>::operator+=(difference_type n)
{
    it -= n;
    return (*this);
}

template <class Iterator>
ReverseRandIter<Iterator>	ReverseRandIter<Iterator>::operator-(difference_type n) const
{
    return (ReverseRandIter<Iterator>(it + n));
}

template <class Iterator>
ReverseRandIter<Iterator>	&ReverseRandIter<Iterator>::operator-=(difference_type n)
{
    it += n;
    return (*this);
}

template <class Iterator>
typename ReverseRandIter<Iterator>::reference ReverseRandIter<Iterator>::operator[](difference_type n) const
{
    return *((*this) + n);
}

template <class Iterator>
bool operator==(const ReverseRandIter<Iterator> &lhs,
                const ReverseRandIter<Iterator> &rhs)
{
    return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(const ReverseRandIter<Iterator> &lhs,
                const ReverseRandIter<Iterator> &rhs)
{
    return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<(const ReverseRandIter<Iterator> &lhs,
               const ReverseRandIter<Iterator> &rhs)
{
    return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator<=(const ReverseRandIter<Iterator> &lhs,
                const ReverseRandIter<Iterator> &rhs)
{
    return lhs.base() >= rhs.base();
}

template <class Iterator>
bool operator>(const ReverseRandIter<Iterator> &lhs,
               const ReverseRandIter<Iterator> &rhs)
{
    return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator>=(const ReverseRandIter<Iterator> &lhs,
                const ReverseRandIter<Iterator> &rhs)
{
    return lhs.base() <= rhs.base();
}

template <class Iterator>
typename ReverseRandIter<Iterator>::ReverseRandIter operator+(
    typename ReverseRandIter<Iterator>::difference_type n,
    const ReverseRandIter<Iterator> &rev_it)
{
    return (rev_it + n);
}

template <class Iterator>
typename ReverseRandIter<Iterator>::difference_type operator-(
    const ReverseRandIter<Iterator> &lhs,
    const ReverseRandIter<Iterator> &rhs)
{
    return (rhs.base() - lhs.base());
}

#endif

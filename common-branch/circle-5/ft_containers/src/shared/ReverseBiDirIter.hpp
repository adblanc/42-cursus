/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseBiDirIter.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 15:18:38 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:53:39 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_BI_DIR_ITERATOR_HPP
#define REVERSE_BI_DIR_ITERATOR_HPP

template <class Iterator>
class ReverseBiDirIter
{
public:
    typedef Iterator iterator_type;
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;

    explicit ReverseBiDirIter(iterator_type it);
    template <class Iter>
    ReverseBiDirIter(const ReverseBiDirIter<Iter> &rev_it);
    ReverseBiDirIter(void);
    ~ReverseBiDirIter();

    ReverseBiDirIter &operator=(const ReverseBiDirIter &rhs);

    iterator_type base() const;

    reference operator*() const;
    ReverseBiDirIter &operator++();
    ReverseBiDirIter operator++(int);
    ReverseBiDirIter &operator--();
    ReverseBiDirIter operator--(int);
    pointer operator->() const;

private:
    iterator_type it;
};

template <class Iterator>
ReverseBiDirIter<Iterator>::ReverseBiDirIter() : it()
{
}

template <class Iterator>
ReverseBiDirIter<Iterator>::ReverseBiDirIter(iterator_type it) : it(it)
{
}

template <class Iterator>
template <class Iter>
ReverseBiDirIter<Iterator>::ReverseBiDirIter(const ReverseBiDirIter<Iter> &rev_it) : it(rev_it.it)
{
}

template <class Iterator>
ReverseBiDirIter<Iterator>::~ReverseBiDirIter()
{
}

template <class Iterator>
typename ReverseBiDirIter<Iterator>::iterator_type ReverseBiDirIter<Iterator>::base() const
{
    return it;
}

template <class Iterator>
ReverseBiDirIter<Iterator>	&ReverseBiDirIter<Iterator>::operator=(const ReverseBiDirIter &rhs)
{
    if (this != &rhs)
    {
        this->it = rhs.it;
    }
    return (*this);
};

template <class Iterator>
typename ReverseBiDirIter<Iterator>::reference ReverseBiDirIter<Iterator>::operator*() const
{
    Iterator itCopy(this->it);

    itCopy--;
    return (*itCopy);
}

template <class Iterator>
typename ReverseBiDirIter<Iterator>::pointer ReverseBiDirIter<Iterator>::operator->() const
{
    Iterator itCopy(this->it);

    itCopy--;
    return (itCopy.operator->());
}

template <class Iterator>
ReverseBiDirIter<Iterator>	&ReverseBiDirIter<Iterator>::operator++()
{
    it--;
    return (*this);
}

template <class Iterator>
ReverseBiDirIter<Iterator>	ReverseBiDirIter<Iterator>::operator++(int)
{
    ReverseBiDirIter tmp(*this);

    ++(*this);
    return (tmp);
}

template <class Iterator>
ReverseBiDirIter<Iterator>	&ReverseBiDirIter<Iterator>::operator--()
{
    it++;
    return (*this);
}

template <class Iterator>
ReverseBiDirIter<Iterator>	ReverseBiDirIter<Iterator>::operator--(int)
{
    ReverseBiDirIter tmp(*this);

    --(*this);
    return (tmp);
}

template <class Iterator>
bool operator==(const ReverseBiDirIter<Iterator> &lhs,
                const ReverseBiDirIter<Iterator> &rhs)
{
    return lhs.base() == rhs.base();
}
template <class Iterator>
bool operator!=(const ReverseBiDirIter<Iterator> &lhs,
                const ReverseBiDirIter<Iterator> &rhs)
{
    return lhs.base() != rhs.base();
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:04:42 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/24 15:04:45 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "utils.hpp"
#include "../shared/IteratorTypes.hpp"

template <typename T>
class Iterator
{
public:
    typedef Node<T> node;

    Iterator(void);
    Iterator(node *ptr);
    Iterator(const Iterator &src);
    ~Iterator();
    Iterator &operator=(const Iterator &rhs);

    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
    typedef ft::bidirectional_iterator_tag iterator_category;

    reference operator*(void) const;
    pointer operator->(void) const;
    Iterator &operator++();
    Iterator &operator--();
    Iterator operator++(int dummy);
    Iterator operator--(int dummy);

    bool operator==(const Iterator &rhs) const;
    bool operator!=(const Iterator &rhs) const;

    node *ptr;

private:
};

template <typename T>
Iterator<T>::Iterator(void){

};

template <typename T>
Iterator<T>::Iterator(node *ptr)
{
    this->ptr = ptr;
};

template <typename T>
Iterator<T>::Iterator(const Iterator &src)
{
    *this = src;
};

template <typename T>
Iterator<T>::~Iterator(){

};

template <typename T>
Iterator<T> &Iterator<T>::operator=(const Iterator &rhs)
{
    if (this != &rhs)
    {
        this->ptr = rhs.ptr;
    }
    return (*this);
};

template <typename T>
typename Iterator<T>::reference Iterator<T>::operator*(void) const
{
    return this->ptr->data;
}

template <typename T>
typename Iterator<T>::pointer Iterator<T>::operator->(void) const
{
    return &this->ptr->data;
}

template <typename T>
Iterator<T> &Iterator<T>::operator++()
{
    ptr = ptr->next;
    return (*this);
}

template <typename T>
Iterator<T> &Iterator<T>::operator--()
{
    ptr = ptr->prev;
    return (*this);
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int dummy)
{
    (void)dummy;
    Iterator<T> copy = *this;
    this->ptr = ptr->next;
    return (copy);
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int dummy)
{
    (void)dummy;
    Iterator<T> copy = *this;
    this->ptr = ptr->prev;
    return (copy);
}

template <typename T>
bool Iterator<T>::operator==(const Iterator &rhs) const
{
    return this->ptr == rhs.ptr;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator &rhs) const
{
    return this->ptr != rhs.ptr;
}

#endif

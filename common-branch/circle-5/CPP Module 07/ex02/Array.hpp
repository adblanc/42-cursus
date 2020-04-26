/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:13:59 by adrien            #+#    #+#             */
/*   Updated: 2020/03/09 17:31:22 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

template <typename T>
class Array
{
public:
    Array(void);
    Array(unsigned int n);
    Array(const Array &src);
    ~Array();

    Array &operator=(const Array &rhs);
    T &operator[](int);

    unsigned int size(void) const;
    void print(void);

private:
    T *ptr;
    unsigned int length;
    void deepCopy(const Array &s);
};

template <typename T>
Array<T>::Array(void)
{
    this->length = 0;
    this->ptr = new T[0]();
}

template <typename T>
Array<T>::Array(unsigned int n)
{
    this->ptr = new T[n]();
    this->length = n;
}

template <typename T>
Array<T>::~Array(void)
{
    delete[] this->ptr;
}

template <typename T>
Array<T>::Array(const Array &src)
{
    if (src.ptr)
    {
        this->deepCopy(src);
    }
    else
    {
        this->length = 0;
        this->ptr = new T[0];
    }
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs)
{
    if (this != &rhs)
    {
        delete[] this->ptr;
        this->deepCopy(rhs);
    }
    return (*this);
}

template <typename T>
T &Array<T>::operator[](int i)
{
    if (!this->ptr || i < 0 || i >= static_cast<int>(this->length))
        throw std::out_of_range("Access is out of range.");
    return (this->ptr[i]);
}

template <typename T>
void Array<T>::deepCopy(const Array &s)
{
    this->length = s.length;
    this->ptr = new T[s.length];

    for (unsigned int i = 0; i < this->length; i++)
        this->ptr[i] = s.ptr[i];
}

template <typename T>
void Array<T>::print(void)
{
    for (unsigned int i = 0; i < this->length; i++)
    {
        std::cout << this->ptr[i] << std::endl;
    }
}

template <typename T>
unsigned int Array<T>::size(void) const
{
    return (this->length);
}

#endif

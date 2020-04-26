/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:58:34 by adrien            #+#    #+#             */
/*   Updated: 2020/03/11 11:10:18 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <list>
#include <iterator>
#include <iostream>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
    typedef typename std::list<T>::iterator iterator;

    MutantStack(void);
    MutantStack(const MutantStack &src);
    ~MutantStack();

    MutantStack &operator=(const MutantStack &rhs);

    void push(T const &value)
    {
        this->list.push_back(value);
    }

    void pop(void)
    {
        this->list.pop_back();
    }

    T top(void)
    {
        return (this->list.back());
    }

    int size(void)
    {
        return (this->list.size());
    }

    iterator begin(void)
    {
        return (this->list.begin());
    }

    iterator end(void)
    {
        return (this->list.end());
    }

private:
    std::list<T> list;
};

template <typename T>
MutantStack<T>::MutantStack(void){

};

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &src) : std::stack<T>()
{
    *this = src;
};

template <typename T>
MutantStack<T>::~MutantStack(){

};

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack<T> &rhs)
{
    if (this != &rhs)
    {
        this->list = rhs.list;
    }
    return (*this);
};

#endif

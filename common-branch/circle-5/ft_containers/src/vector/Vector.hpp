/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:07:12 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/24 15:31:42 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <exception>
#include <stdexcept>
#include <string>
#include <limits>
#include "./RandIter.hpp"
#include "../shared/ReverseRandIter.hpp"

namespace ft
{

  template <typename T>
  class vector
  {
  public:
    typedef T value_type;
    typedef RandIter<T> iterator;
    typedef RandIter<const T> const_iterator;
    typedef ReverseRandIter<iterator> reverse_iterator;
    typedef ReverseRandIter<const_iterator> const_reverse_iterator;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

    // Default, fill, range, copy constructors, destructor and assignation.

    explicit vector(void);
    explicit vector(size_type n, const value_type &val = value_type());
    template <class InputIterator>
    vector(InputIterator first, InputIterator last);
    vector(const vector &src);
    ~vector();
    vector &operator=(const vector &rhs);

    // Iterators

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;

    reverse_iterator rend();
    const_reverse_iterator rend() const;

    // Capacity

    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    void resize(size_type n, value_type val = value_type());
    size_type capacity() const;
    void reserve(size_type n);

    // Element access

    reference operator[](size_type n);
    const_reference operator[](size_type n) const;

    reference at(size_type n);
    const_reference at(size_type n) const;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    // Modifiers

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type &val);

    void push_back(const value_type &val);
    void pop_back();

    iterator insert(iterator position, const value_type &val);
    void insert(iterator position, size_type n, const value_type &val);
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last);

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);

    void swap(vector &x);
    void clear();

  private:
    size_type getOptimizedCapacity(size_type elementsNbr);
    void moveElemsToTheRight(size_t index, size_t offset);
    T *arr;

    size_type allocatedCapacity;
    size_type length;
  };

  // Implementation

  template <class T>
  vector<T>::vector(void) : arr(NULL), allocatedCapacity(0), length(0){};

  template <class T>
  vector<T>::vector(size_type n, const value_type &val) : arr(NULL), allocatedCapacity(0), length(0)
  {
    assign(n, val);
  };

  template <class T>
  template <class InputIterator>
  vector<T>::vector(InputIterator first, InputIterator last) : arr(NULL), allocatedCapacity(0), length(0)
  {
    assign(first, last);
  }

  template <class T>
  vector<T>::vector(const vector<T> &src) : arr(NULL), allocatedCapacity(0), length(0)
  {
    assign(src.begin(), src.end());
  };

  template <class T>
  vector<T> &vector<T>::operator=(const vector<T> &rhs)
  {
    if (this != &rhs)
    {
      assign(rhs.begin(), rhs.end());
    }
    return (*this);
  };

  template <class T>
  vector<T>::~vector()
  {
    std::allocator<T> alloc;

    clear();
    alloc.deallocate(arr, capacity());
  };

  template <class T>
  void vector<T>::clear()
  {
    erase(begin(), end());
  }

  template <class T>
  typename vector<T>::reference vector<T>::at(size_type n)
  {
    if (n < 0 || n >= size())
      throw std::out_of_range("Index is out of range");
    return (*this)[n];
  }

  template <class T>
  typename vector<T>::const_reference vector<T>::at(size_type n) const
  {
    if (n < 0 || n >= size())
      throw std::out_of_range("Index is out of range");
    return (*this)[n];
  }

  template <class T>
  typename vector<T>::reference vector<T>::operator[](size_type n)
  {
    return arr[n];
  }

  template <class T>
  typename vector<T>::const_reference vector<T>::operator[](size_type n) const
  {
    return arr[n];
  }

  template <class T>
  void vector<T>::pop_back()
  {
    erase(--end());
  }

  template <class T>
  typename vector<T>::size_type vector<T>::size() const
  {
    return this->length;
  }

  template <class T>
  bool vector<T>::empty() const
  {
    return this->length == 0;
  }

  template <class T>
  typename vector<T>::reference vector<T>::front()
  {
    return (*begin());
  }

  template <class T>
  typename vector<T>::const_reference vector<T>::front() const
  {
    return (*begin());
  }

  template <class T>
  typename vector<T>::iterator vector<T>::begin()
  {
    return vector<T>::iterator(arr);
  }

  template <class T>
  typename vector<T>::const_iterator vector<T>::begin() const
  {
    return vector<T>::const_iterator(arr);
  }

  template <class T>
  typename vector<T>::reverse_iterator vector<T>::rend()
  {
    return vector<T>::reverse_iterator(begin());
  }

  template <class T>
  typename vector<T>::const_reverse_iterator vector<T>::rend() const
  {
    return vector<T>::const_reverse_iterator(begin());
  }

  template <class T>
  typename vector<T>::reference vector<T>::back()
  {
    return (*--end());
  }

  template <class T>
  typename vector<T>::const_reference vector<T>::back() const
  {
    return (*--end());
  }

  template <class T>
  typename vector<T>::iterator vector<T>::end()
  {
    return vector<T>::iterator(arr + length);
  }

  template <class T>
  typename vector<T>::const_iterator vector<T>::end() const
  {
    return vector<T>::const_iterator(arr + length);
  }

  template <class T>
  typename vector<T>::reverse_iterator vector<T>::rbegin()
  {
    return vector<T>::reverse_iterator(end());
  }

  template <class T>
  typename vector<T>::const_reverse_iterator vector<T>::rbegin() const
  {
    return vector<T>::const_reverse_iterator(end());
  }

  template <class T>
  template <class InputIterator>
  void vector<T>::assign(InputIterator first, InputIterator last)
  {
    clear();
    insert(begin(), first, last);
  }

  template <class T>
  void vector<T>::assign(size_type n, const value_type &val)
  {
    clear();
    insert(begin(), n, val);
  }

  template <class T>
  void vector<T>::push_back(const value_type &val)
  {
    reserve(getOptimizedCapacity(length + 1));
    insert(end(), val);
  }

  template <class T>
  typename vector<T>::size_type vector<T>::getOptimizedCapacity(size_type elementsNbr)
  {
    if (!capacity())
      return elementsNbr;

    size_type newCapacity = capacity();
    while (elementsNbr > newCapacity)
      newCapacity *= 2;

    return newCapacity;
  }

  template <class T>
  typename vector<T>::iterator vector<T>::insert(iterator position, const value_type &val)
  {
    insert(position, (size_type)1, val);

    return position;
  }

  template <class T>
  void vector<T>::insert(iterator position, size_type n, const value_type &val)
  {
    if (!n)
      return;

    size_t elemIndex = position - begin();
    std::allocator<T> alloc;

    reserve(length + n);

    moveElemsToTheRight(elemIndex, n);

    for (size_t i = 0; i < n; i++)
      alloc.construct(&arr[elemIndex + i], val);

    length += n;
  }

  template <class T>
  void vector<T>::reserve(size_type n)
  {
    if (n > max_size())
      throw std::length_error("reserve: The requested size exceed max_size that ft::vector can handle.");
    if (n <= capacity())
      return;

    std::allocator<T> alloc;

    T *new_array = alloc.allocate(n);
    for (size_t i = 0; i < length; i++)
    {
      alloc.construct(&new_array[i], arr[i]);
      alloc.destroy(&arr[i]);
    }

    alloc.deallocate(arr, capacity());
    allocatedCapacity = n;
    arr = new_array;
  }

  template <class T>
  void vector<T>::moveElemsToTheRight(size_t index, size_t offset)
  {
    std::allocator<T> alloc;

    if (!size())
      return;

    for (size_t i = size(); i >= index && i-- > 0;)
    {
      alloc.construct(&arr[i + offset], arr[i]);
      alloc.destroy(&arr[i]);
    }
  }

  template <class T>
  template <class InputIterator>
  void vector<T>::insert(iterator position, InputIterator first, InputIterator last)
  {
    size_t elemIndex = position - begin();
    size_t n = last - first;
    std::allocator<T> alloc;

    reserve(length + n);

    moveElemsToTheRight(elemIndex, n);

    for (size_t i = 0; i < n; i++)
      alloc.construct(&arr[elemIndex + i], *(first + i));

    length += n;
  }

  template <class T>
  typename vector<T>::iterator vector<T>::erase(iterator position)
  {
    return erase(position, position + 1);
  }

  template <class T>
  typename vector<T>::iterator vector<T>::erase(iterator first, iterator last)
  {
    size_type nbrToErase = last - first;
    std::allocator<T> alloc;

    size_t start = first - begin();
    size_t end = start + nbrToErase;

    for (size_t i = start; i < end; i++)
      alloc.destroy(arr + i);

    for (size_t i = end; i < length; i++)
    {
      alloc.construct(&arr[i - nbrToErase], arr[i]);
      alloc.destroy(&arr[i]);
    }
    length -= nbrToErase;
    return first;
  }

  template <class T>
  typename vector<T>::size_type vector<T>::capacity() const
  {
    return allocatedCapacity;
  }

  template <class T>
  void vector<T>::resize(size_type n, value_type val)
  {
    if (n < size())
    {
      iterator it = begin();
      for (size_type i = 0; i < n; i++)
        it++;
      erase(it, end());
    }
    else
      insert(end(), n - size(), val);
  }

  template <class T>
  typename vector<T>::size_type vector<T>::max_size() const
  {
    return std::numeric_limits<difference_type>::max();
  }

  template <class T>
  void vector<T>::swap(vector &x)
  {
    T *tmp_arr(arr);
    size_t tmp_length(size());
    size_t tmp_cap(capacity());

    arr = x.arr;
    length = x.size();
    allocatedCapacity = x.capacity();

    x.arr = tmp_arr;
    x.length = tmp_length;
    x.allocatedCapacity = tmp_cap;
  }

  // Non-member function overloads
  // Relational operators
  template <class T>
  bool operator==(const vector<T> &lhs, const vector<T> &rhs)
  {
    if (lhs.size() != rhs.size())
      return false;

    typename vector<T>::const_iterator it_lhs = lhs.begin();
    typename vector<T>::const_iterator it_rhs = rhs.begin();

    for (; it_lhs != lhs.end(); it_lhs++, it_rhs++)
    {
      if (*it_lhs != *it_rhs)
        return (false);
    }
    return (true);
  }

  template <class T>
  bool operator!=(const vector<T> &lhs, const vector<T> &rhs)
  {
    return !(lhs == rhs);
  }
  template <class T>
  bool operator<(const vector<T> &lhs, const vector<T> &rhs)
  {
    typename vector<T>::const_iterator it_lhs = lhs.begin();
    typename vector<T>::const_iterator it_rhs = rhs.begin();

    for (; it_rhs != rhs.end(); it_lhs++, it_rhs++)
    {
      if (it_lhs == lhs.end() || *it_lhs < *it_rhs)
        return true;
    }
    return (false);
  }
  template <class T>
  bool operator<=(const vector<T> &lhs, const vector<T> &rhs)
  {
    return !(lhs > rhs);
  }
  template <class T>
  bool operator>(const vector<T> &lhs, const vector<T> &rhs)
  {
    return (rhs < lhs);
  }
  template <class T>
  bool operator>=(const vector<T> &lhs, const vector<T> &rhs)
  {
    return !(lhs < rhs);
  }
  // swap
  template <class T>
  void swap(vector<T> &x, vector<T> &y)
  {
    x.swap(y);
  }

} // namespace ft

#endif

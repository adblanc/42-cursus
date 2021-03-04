/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:04:00 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:17:39 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <string>
#include <limits>
#include "Iterator.hpp"
#include "ReverseIterator.hpp"

#include "utils.hpp"

namespace ft
{

  template <typename T>
  class list
  {
  public:
    typedef T value_type;
    typedef Iterator<T> iterator;
    typedef Iterator<const T> const_iterator;
    typedef ReverseIterator<Iterator<T> > reverse_iterator;
    typedef ReverseIterator<Iterator<const T> > const_reverse_iterator;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

    // Default, fill, range, copy constructors, destructor and assignation.

    explicit list(void);
    explicit list(size_type n, const value_type &val = value_type());
    template <class InputIterator>
    explicit list(InputIterator first, InputIterator last);
    list(const list &src);
    ~list();
    list &operator=(const list &rhs);

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

    // Element access

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    // Modifiers

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type &val);

    void push_front(const value_type &val);
    void pop_front();
    void push_back(const value_type &val);
    void pop_back();

    iterator insert(iterator position, const value_type &val);
    void insert(iterator position, size_type n, const value_type &val);
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last);

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);

    void swap(list &x);
    void resize(size_type n, value_type val = value_type());
    void clear();

    // Operations

    void splice(iterator position, list &x);
    void splice(iterator position, list &x, iterator i);
    void splice(iterator position, list &x, iterator first, iterator last);

    void remove(const value_type &val);
    template <class Predicate>
    void remove_if(Predicate pred);

    void unique();
    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred);

    void merge(list &x);
    template <class Compare>
    void merge(list &x, Compare comp);

    void sort();
    template <class Compare>
    void sort(Compare comp);

    void reverse();

  private:
    typedef Node<T> node;

    size_type length;
    node *head;
    node *createNewNode(const T &data);
    void deleteNode(node *elem);
    void initHeadAndLength();

    void swapNodes(node *a, node *b);

    static bool is_less(const_reference, const_reference);
    static bool is_equal(const_reference, const_reference);
  };

  // Implementation

  template <class T>
  list<T>::list(void)
  {
    initHeadAndLength();
  };

  template <class T>
  void list<T>::initHeadAndLength()
  {
    head = new node;
    head->next = head;
    head->prev = head;
    head->data = T();
    length = 0;
  }

  template <class T>
  list<T>::list(size_type n, const value_type &val)
  {
    initHeadAndLength();
    assign(n, val);
  };

  template <class T>
  template <class InputIterator>
  list<T>::list(InputIterator first, InputIterator last)
  {
    initHeadAndLength();
    assign(first, last);
  }

  template <class T>
  list<T>::list(const list<T> &src)
  {
    initHeadAndLength();
    assign(src.begin(), src.end());
  };

  template <class T>
  list<T> &list<T>::operator=(const list<T> &rhs)
  {
    if (this != &rhs)
    {
      assign(rhs.begin(), rhs.end());
    }
    return (*this);
  };

  template <class T>
  list<T>::~list()
  {
    clear();
    delete head;
  };

  template <class T>
  void list<T>::clear()
  {
    erase(begin(), end());
  }

  template <typename T>
  typename list<T>::iterator list<T>::erase(iterator first, iterator last)
  {
    iterator it = first;

    while (it != last)
      erase(it++);
    return it;
  }

  template <typename T>
  typename list<T>::iterator list<T>::erase(iterator position)
  {
    node *current = position.ptr;
    node *left = current->prev;
    node *right = current->next;

    left->next = right;
    right->prev = left;
    deleteNode(current);

    return right;
  }

  template <class T>
  void list<T>::deleteNode(node *elem)
  {
    length--;
    delete elem;
  }

  template <class T>
  void list<T>::push_front(const value_type &val)
  {
    insert(begin(), val);
  }

  template <class T>
  void list<T>::push_back(const value_type &val)
  {
    insert(end(), val);
  }

  template <typename T>
  void list<T>::insert(iterator position, size_type n, const value_type &val)
  {
    for (size_t i = 0; i < n; i++)
      insert(position, val);
  }

  template <typename T>
  template <class InputIterator>
  void list<T>::insert(iterator position, InputIterator first, InputIterator last)
  {
    for (InputIterator it = first; it != last; it++)
      insert(position, *it);
  }

  template <typename T>
  typename list<T>::iterator list<T>::insert(iterator position, const value_type &val)
  {
    node *newNode = createNewNode(val);

    node *left = position.ptr->prev;
    node *right = position.ptr;

    newNode->next = right;
    newNode->prev = left;

    left->next = newNode;
    right->prev = newNode;

    length++;

    return iterator(newNode);
  }

  template <class T>
  typename list<T>::node *list<T>::createNewNode(const T &data)
  {
    node *newNode = new node;

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
  }

  template <class T>
  void list<T>::pop_back()
  {
    erase(--end());
  }

  template <class T>
  void list<T>::pop_front()
  {
    erase(begin());
  }

  template <class T>
  typename list<T>::size_type list<T>::size() const
  {
    return this->length;
  }

  template <class T>
  bool list<T>::empty() const
  {
    return this->length == 0;
  }

  template <class T>
  typename list<T>::reference list<T>::front()
  {
    return (*begin());
  }

  template <class T>
  typename list<T>::const_reference list<T>::front() const
  {
    return (*begin());
  }

  template <class T>
  typename list<T>::iterator list<T>::begin()
  {
    return list<T>::iterator(head->next);
  }

  template <class T>
  typename list<T>::const_iterator list<T>::begin() const
  {
    return list<T>::const_iterator(reinterpret_cast<Node<const T> *>(head->next));
  }

  template <class T>
  typename list<T>::reverse_iterator list<T>::rend()
  {
    return list<T>::reverse_iterator(begin());
  }

  template <class T>
  typename list<T>::const_reverse_iterator list<T>::rend() const
  {
    return list<T>::const_reverse_iterator(begin());
  }

  template <class T>
  typename list<T>::reference list<T>::back()
  {
    return (*--end());
  }

  template <class T>
  typename list<T>::const_reference list<T>::back() const
  {
    return (*--end());
  }

  template <class T>
  typename list<T>::iterator list<T>::end()
  {
    return list<T>::iterator(head);
  }

  template <class T>
  typename list<T>::const_iterator list<T>::end() const
  {
    return list<T>::const_iterator(reinterpret_cast<Node<const T> *>(head));
  }

  template <class T>
  typename list<T>::reverse_iterator list<T>::rbegin()
  {
    return list<T>::reverse_iterator(end());
  }

  template <class T>
  typename list<T>::const_reverse_iterator list<T>::rbegin() const
  {
    return list<T>::const_reverse_iterator(end());
  }

  template <class T>
  void list<T>::remove(const value_type &val)
  {
    for (iterator it = begin(); it != end();)
    {
      if (*it == val)
        it = erase(it);
      else
        it++;
    }
  }

  template <class T>
  template <class Predicate>
  void list<T>::remove_if(Predicate pred)
  {
    for (iterator it = begin(); it != end();)
    {
      if (pred(*it) == true)
        it = erase(it);
      else
        it++;
    }
  }

  template <class T>
  void list<T>::unique()
  {
    unique(is_equal);
  }

  template <class T>
  template <class BinaryPredicate>
  void list<T>::unique(BinaryPredicate binary_pred)
  {
    iterator it = begin();
    iterator it_right = ++begin();

    while (it_right != end())
    {
      if (binary_pred(*it, *it_right))
        it_right = erase(it_right);
      else
      {
        it++;
        it_right++;
      }
    }
  }

  template <class T>
  bool list<T>::is_equal(const_reference a, const_reference b)
  {
    return (a == b);
  }

  template <class T>
  template <class InputIterator>
  void list<T>::assign(InputIterator first, InputIterator last)
  {
    clear();
    insert(begin(), first, last);
  }

  template <class T>
  void list<T>::assign(size_type n, const value_type &val)
  {
    clear();
    insert(begin(), n, val);
  }

  template <class T>
  void list<T>::swap(list<T> &x)
  {
    node *tmp = head;
    size_type tmp_length = size();

    head = x.head;
    length = x.length;
    head->prev->next = head;
    head->next->prev = head;

    x.head = tmp;
    x.length = tmp_length;
    x.head->prev->next = x.head;
    x.head->next->prev = x.head;
  }

  template <class T>
  void list<T>::resize(size_type n, value_type val)
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
  typename list<T>::size_type list<T>::max_size() const
  {
    return std::numeric_limits<size_t>::max();
  }

  template <class T>
  void list<T>::splice(iterator position, list &x)
  {
    splice(position, x, x.begin(), x.end());
  }

  template <class T>
  void list<T>::splice(iterator position, list &x, iterator i)
  {
    node *current = position.ptr;
    node *prev = (--position).ptr;
    node *toAdd = i.ptr;

    toAdd->prev->next = toAdd->next;
    toAdd->next->prev = toAdd->prev;

    prev->next = toAdd;
    toAdd->prev = prev;

    toAdd->next = current;
    current->prev = toAdd;

    length++;
    x.length--;
  }

  template <class T>
  void list<T>::splice(iterator position, list &x, iterator first, iterator last)
  {
    iterator temp = first;
    iterator it = first;

    while (it != last)
    {
      temp++;
      splice(position, x, it);
      it = temp;
    }
  }

  template <class T>
  void list<T>::reverse()
  {
    node *tmp;
    node *tmp_next;

    tmp = head;
    tmp_next = head->next;

    tmp->next = tmp->prev;
    tmp->prev = tmp_next;
    tmp = tmp_next;
    while (tmp != head)
    {
      tmp_next = tmp->next;
      tmp->next = tmp->prev;
      tmp->prev = tmp_next;
      tmp = tmp_next;
    }
  }

  template <typename T>
  void list<T>::merge(list &x)
  {
    merge(x, is_less);
  }

  template <class T>
  template <class Compare>
  void list<T>::merge(list &x, Compare comp)
  {
    if (&x == this)
      return;

    typename list<T>::iterator it = begin();
    for (; it != end() && !x.empty(); it++)
      while (!x.empty() && comp(x.front(), *it))
        splice(it, x, x.begin());

    if (!x.empty())
      splice(end(), x, x.begin(), x.end());
  }

  template <class T>
  void list<T>::sort()
  {
    sort(is_less);
  }

  template <class T>
  template <class Compare>
  void list<T>::sort(Compare comp)
  {
    bool swapped = true;
    node *ptr;

    if (empty())
      return;

    while (swapped)
    {
      swapped = false;
      ptr = head->next;
      while (ptr->next != head)
      {
        if (comp(ptr->next->data, ptr->data))
        {
          swapped = true;
          swapNodes(ptr, ptr->next);
        }
        else
          ptr = ptr->next;
      }
    }
  }

  template <class T>
  void list<T>::swapNodes(node *a, node *b)
  {
    node *left = a->prev;
    node *current = a;
    node *right = b;

    left->next = right;
    current->prev = right;
    right->prev = left;
    current->next = right->next;
    right->next->prev = current;
    right->next = current;
  }

  template <class T>
  bool list<T>::is_less(const_reference a, const_reference b)
  {
    return (a < b);
  }

  // Non-member function overloads
  // Relational operators
  template <class T>
  bool operator==(const list<T> &lhs, const list<T> &rhs)
  {
    if (lhs.size() != rhs.size())
      return false;
    return !(lhs > rhs || lhs < rhs);
  }
  template <class T>
  bool operator!=(const list<T> &lhs, const list<T> &rhs)
  {
    return !(lhs == rhs);
  }
  template <class T>
  bool operator<(const list<T> &lhs, const list<T> &rhs)
  {
    return (rhs > lhs);
  }
  template <class T>
  bool operator<=(const list<T> &lhs, const list<T> &rhs)
  {
    return !(lhs > rhs);
  }
  template <class T>
  bool operator>(const list<T> &lhs, const list<T> &rhs)
  {
    typename list<T>::const_iterator it_lhs = lhs.begin();
    typename list<T>::const_iterator it_rhs = rhs.begin();

    for (; it_lhs != lhs.end(); it_lhs++, it_rhs++)
    {
      if (it_rhs == rhs.end() || *it_lhs > *it_rhs)
        return (true);
    }
    return (false);
  }
  template <class T>
  bool operator>=(const list<T> &lhs, const list<T> &rhs)
  {
    return !(lhs < rhs);
  }
  // swap
  template <class T>
  void swap(list<T> &x, list<T> &y)
  {
    x.swap(y);
  }

} // namespace ft

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:16:15 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:29:02 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include <exception>
#include <string>
#include <limits>
#include "../shared/ReverseBiDirIter.hpp"
#include "../shared/Pair.hpp"
#include "../shared/RedBlackTree.hpp"
#include "../shared/RedBlackTreeIterator.hpp"
#include "../shared/Less.hpp"

namespace ft
{

template <class T, class Compare = ft::Less<T> >
class set
{
public:
    // Member types

    typedef T key_type;
    typedef T value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef std::allocator<value_type> allocator_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef RedBlackTreeIterator<value_type, value_compare, false> iterator;
    typedef RedBlackTreeIterator<const value_type, value_compare, false> const_iterator;
    typedef ReverseBiDirIter<iterator> reverse_iterator;
    typedef ReverseBiDirIter<const_iterator> const_reverse_iterator;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

    explicit set(const key_compare &comp = key_compare());
    template <class InputIterator>
    set(InputIterator first, InputIterator last,
        const key_compare &comp = key_compare());
    set(const set &src);

    ~set();

    set &operator=(const set &rhs);

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

    // Modifiers

    ft::Pair<iterator, bool> insert(const value_type &val);
    iterator insert(iterator position, const value_type &val);
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last);

    void erase(iterator position);
    size_type erase(const value_type &val);
    void erase(iterator first, iterator last);

    void swap(set &x);
    void clear();

    // Observers

    key_compare key_comp() const;
    value_compare value_comp() const;

    // Operations

    iterator find(const value_type &val);
    const_iterator find(const value_type &val) const;

    size_type count(const value_type &val) const;

    iterator lower_bound(const value_type &val);
    const_iterator lower_bound(const value_type &val) const;

    iterator upper_bound(const value_type &val);
    const_iterator upper_bound(const value_type &val) const;

    ft::Pair<const_iterator, const_iterator> equal_range(const value_type &val) const;
    ft::Pair<iterator, iterator> equal_range(const value_type &val);

private:
    key_compare comp;

    static bool keysAreTheSame(const value_type &val1, const value_type &val2)
    {
        Compare comp;

        return !(comp(val1, val2) || comp(val2, val1));
    };

    static bool keyIsGreaterOrEqual(const value_type &val1, const value_type &val2)
    {
        Compare comp;

        return (!comp(val2, val1));
    };

    static bool keyIsSmaller(const value_type &val1, const value_type &val2)
    {
        Compare comp;

        return comp(val1, val2);
    };

    ft::RedBlackTree<T, value_compare, false> tree;
};

template <class T, class Compare>
set<T, Compare>::set(const key_compare &comp) : comp(comp), tree(value_compare(comp))
{
}

template <class T, class Compare>
template <class InputIterator>
set<T, Compare>::set(InputIterator first, InputIterator last, const key_compare &comp) : tree(first, last, value_compare(comp))
{
}

template <class T, class Compare>
set<T, Compare>::set(const set &src) : tree(src.tree)
{
}

template <class T, class Compare>
set<T, Compare>::~set()
{
}

template <class T, class Compare>
set<T, Compare> &set<T, Compare>::operator=(const set &rhs)
{
    if (this != &rhs)
        tree.operator=(rhs.tree);
    return (*this);
};

// Iterators

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::begin()
{
    return tree.begin();
}

template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::begin() const
{
    return tree.begin();
}
template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::end()
{
    return tree.end();
}
template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::end() const
{
    return tree.end();
}
template <class T, class Compare>
typename set<T, Compare>::reverse_iterator set<T, Compare>::rbegin()
{
    return tree.rbegin();
}
template <class T, class Compare>
typename set<T, Compare>::const_reverse_iterator set<T, Compare>::rbegin() const
{
    return tree.rbegin();
}
template <class T, class Compare>
typename set<T, Compare>::reverse_iterator set<T, Compare>::rend()
{
    return tree.rend();
}
template <class T, class Compare>
typename set<T, Compare>::const_reverse_iterator set<T, Compare>::rend() const
{
    return tree.rend();
}

// Capacity

template <class T, class Compare>
bool set<T, Compare>::empty() const
{
    return tree.empty();
}
template <class T, class Compare>
typename set<T, Compare>::size_type set<T, Compare>::size() const
{
    return tree.size();
}
template <class T, class Compare>
typename set<T, Compare>::size_type set<T, Compare>::max_size() const
{
    return std::numeric_limits<difference_type>::max();
}

// Modifiers

template <class T, class Compare>
ft::Pair<typename set<T, Compare>::iterator, bool> set<T, Compare>::insert(const value_type &val)
{
    size_t length_before = size();
    iterator it = tree.insert(val);

    bool elementInserted = size() > length_before;

    return ft::make_pair<iterator, bool>(it, elementInserted);
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::insert(iterator position, const value_type &val)
{
    return tree.insert(position, val);
}

template <class T, class Compare>
template <class InputIterator>
void set<T, Compare>::insert(InputIterator first, InputIterator last)
{
    tree.insert(first, last);
}

template <class T, class Compare>
void set<T, Compare>::erase(iterator position)
{
    tree.erase(position);
}

template <class T, class Compare>
typename set<T, Compare>::size_type set<T, Compare>::erase(const value_type &val)
{
    return tree.eraseIf(keysAreTheSame, val);
}

template <class T, class Compare>
void set<T, Compare>::erase(iterator first, iterator last)
{
    tree.erase(first, last);
}

template <class T, class Compare>
void set<T, Compare>::swap(set &x)
{
    tree.swap(x.tree);
}

template <class T, class Compare>
void set<T, Compare>::clear()
{
    tree.clear();
}

// Observers

template <class T, class Compare>
typename set<T, Compare>::key_compare set<T, Compare>::key_comp() const
{
    return key_compare();
}

template <class T, class Compare>
typename set<T, Compare>::value_compare set<T, Compare>::value_comp() const
{
    return value_compare(Compare());
}

// Operations

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::find(const value_type &val)
{
    return tree.find(keysAreTheSame, val);
}
template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::find(const value_type &val) const
{
    return tree.find(keysAreTheSame, val);
}

template <class T, class Compare>
typename set<T, Compare>::size_type set<T, Compare>::count(const value_type &val) const
{
    return tree.countIf(keysAreTheSame, val);
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::lower_bound(const value_type &val)
{
    return tree.find(keyIsGreaterOrEqual, val);
}
template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::lower_bound(const value_type &val) const
{
    return tree.find(keyIsGreaterOrEqual, val);
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::upper_bound(const value_type &val)
{
    return tree.find(keyIsSmaller, val);
}
template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::upper_bound(const value_type &val) const
{
    return tree.find(keyIsSmaller, val);
}

template <class T, class Compare>
ft::Pair<typename set<T, Compare>::const_iterator, typename set<T, Compare>::const_iterator> set<T, Compare>::equal_range(const value_type &val) const
{
    return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
}
template <class T, class Compare>
ft::Pair<typename set<T, Compare>::iterator, typename set<T, Compare>::iterator> set<T, Compare>::equal_range(const value_type &val)
{
    return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
}

} // namespace ft

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiset.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:16:15 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:19:11 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_SET_HPP
#define MULTI_SET_HPP

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
class multiset
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
    typedef RedBlackTreeIterator<value_type, value_compare, true> iterator;
    typedef RedBlackTreeIterator<const value_type, value_compare, true> const_iterator;
    typedef ReverseBiDirIter<iterator> reverse_iterator;
    typedef ReverseBiDirIter<const_iterator> const_reverse_iterator;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

    explicit multiset(const key_compare &comp = key_compare());
    template <class InputIterator>
    multiset(InputIterator first, InputIterator last,
             const key_compare &comp = key_compare());
    multiset(const multiset &src);

    ~multiset();

    multiset &operator=(const multiset &rhs);

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

    iterator insert(const value_type &val);
    iterator insert(iterator position, const value_type &val);
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last);

    void erase(iterator position);
    size_type erase(const value_type &val);
    void erase(iterator first, iterator last);

    void swap(multiset &x);
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

    ft::RedBlackTree<T, value_compare, true> tree;
};

template <class T, class Compare>
multiset<T, Compare>::multiset(const key_compare &comp) : comp(comp), tree(value_compare(comp))
{
}

template <class T, class Compare>
template <class InputIterator>
multiset<T, Compare>::multiset(InputIterator first, InputIterator last, const key_compare &comp) : tree(first, last, value_compare(comp))
{
}

template <class T, class Compare>
multiset<T, Compare>::multiset(const multiset &src) : tree(src.tree)
{
}

template <class T, class Compare>
multiset<T, Compare>::~multiset()
{
}

template <class T, class Compare>
multiset<T, Compare> &multiset<T, Compare>::operator=(const multiset &rhs)
{
    if (this != &rhs)
        tree.operator=(rhs.tree);
    return (*this);
};

// Iterators

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::begin()
{
    return tree.begin();
}

template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::begin() const
{
    return tree.begin();
}
template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::end()
{
    return tree.end();
}
template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::end() const
{
    return tree.end();
}
template <class T, class Compare>
typename multiset<T, Compare>::reverse_iterator multiset<T, Compare>::rbegin()
{
    return tree.rbegin();
}
template <class T, class Compare>
typename multiset<T, Compare>::const_reverse_iterator multiset<T, Compare>::rbegin() const
{
    return tree.rbegin();
}
template <class T, class Compare>
typename multiset<T, Compare>::reverse_iterator multiset<T, Compare>::rend()
{
    return tree.rend();
}
template <class T, class Compare>
typename multiset<T, Compare>::const_reverse_iterator multiset<T, Compare>::rend() const
{
    return tree.rend();
}

// Capacity

template <class T, class Compare>
bool multiset<T, Compare>::empty() const
{
    return tree.empty();
}
template <class T, class Compare>
typename multiset<T, Compare>::size_type multiset<T, Compare>::size() const
{
    return tree.size();
}
template <class T, class Compare>
typename multiset<T, Compare>::size_type multiset<T, Compare>::max_size() const
{
    return std::numeric_limits<difference_type>::max();
}

// Modifiers

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::insert(const value_type &val)
{
    return tree.insert(val);
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::insert(iterator position, const value_type &val)
{
    return tree.insert(position, val);
}

template <class T, class Compare>
template <class InputIterator>
void multiset<T, Compare>::insert(InputIterator first, InputIterator last)
{
    tree.insert(first, last);
}

template <class T, class Compare>
void multiset<T, Compare>::erase(iterator position)
{
    tree.erase(position);
}

template <class T, class Compare>
typename multiset<T, Compare>::size_type multiset<T, Compare>::erase(const value_type &val)
{
    return tree.eraseIf(keysAreTheSame, val);
}

template <class T, class Compare>
void multiset<T, Compare>::erase(iterator first, iterator last)
{
    tree.erase(first, last);
}

template <class T, class Compare>
void multiset<T, Compare>::swap(multiset &x)
{
    tree.swap(x.tree);
}

template <class T, class Compare>
void multiset<T, Compare>::clear()
{
    tree.clear();
}

// Observers

template <class T, class Compare>
typename multiset<T, Compare>::key_compare multiset<T, Compare>::key_comp() const
{
    return key_compare();
}

template <class T, class Compare>
typename multiset<T, Compare>::value_compare multiset<T, Compare>::value_comp() const
{
    return value_compare(Compare());
}

// Operations

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::find(const value_type &val)
{
    return tree.find(keysAreTheSame, val);
}
template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::find(const value_type &val) const
{
    return tree.find(keysAreTheSame, val);
}

template <class T, class Compare>
typename multiset<T, Compare>::size_type multiset<T, Compare>::count(const value_type &val) const
{
    return tree.countIf(keysAreTheSame, val);
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::lower_bound(const value_type &val)
{
    return tree.find(keyIsGreaterOrEqual, val);
}
template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::lower_bound(const value_type &val) const
{
    return tree.find(keyIsGreaterOrEqual, val);
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::upper_bound(const value_type &val)
{
    return tree.find(keyIsSmaller, val);
}
template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::upper_bound(const value_type &val) const
{
    return tree.find(keyIsSmaller, val);
}

template <class T, class Compare>
ft::Pair<typename multiset<T, Compare>::const_iterator, typename multiset<T, Compare>::const_iterator> multiset<T, Compare>::equal_range(const value_type &val) const
{
    return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
}
template <class T, class Compare>
ft::Pair<typename multiset<T, Compare>::iterator, typename multiset<T, Compare>::iterator> multiset<T, Compare>::equal_range(const value_type &val)
{
    return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
}

} // namespace ft

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multimap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:16:15 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 16:07:55 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_MAP_HPP
#define MULTI_MAP_HPP

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

template <class Key, class T, class Compare = ft::Less<Key> >
class multimap
{
public:
    // Member types
    class value_compare;

    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::Pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
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

    explicit multimap(const key_compare &comp = key_compare());
    template <class InputIterator>
    multimap(InputIterator first, InputIterator last,
             const key_compare &comp = key_compare());
    multimap(const multimap &src);

    ~multimap();

    multimap &operator=(const multimap &rhs);

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
    size_type erase(const key_type &k);
    void erase(iterator first, iterator last);

    void swap(multimap &x);
    void clear();

    // Observers

    key_compare key_comp() const;
    value_compare value_comp() const;

    // Operations

    iterator find(const key_type &k);
    const_iterator find(const key_type &k) const;

    size_type count(const key_type &k) const;

    iterator lower_bound(const key_type &k);
    const_iterator lower_bound(const key_type &k) const;

    iterator upper_bound(const key_type &k);
    const_iterator upper_bound(const key_type &k) const;

    ft::Pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
    ft::Pair<iterator, iterator> equal_range(const key_type &k);

private:
    key_compare comp;

    static bool keysAreTheSame(const ft::Pair<const Key, T> &p1, const ft::Pair<const Key, T> &p2)
    {
        Compare comp;

        return !(comp(p1.first, p2.first) || comp(p2.first, p1.first));
    };

    static bool keyIsGreaterOrEqual(const ft::Pair<const Key, T> &p1, const ft::Pair<const Key, T> &p2)
    {
        Compare comp;

        return (!comp(p2.first, p1.first));
    };

    static bool keyIsSmaller(const ft::Pair<const Key, T> &p1, const ft::Pair<const Key, T> &p2)
    {
        Compare comp;

        return comp(p1.first, p2.first);
    };

    ft::RedBlackTree<ft::Pair<const Key, T>, value_compare, true> tree;
};

template <class Key, class T, class Compare>
class multimap<Key, T, Compare>::value_compare : ft::BinaryFunction<value_type, value_type, bool>
{
    friend class multimap;

protected:
    Compare comp;
    value_compare(Compare c);

public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const;
};

template <class Key, class T, class Compare>
multimap<Key, T, Compare>::value_compare::value_compare(Compare c) : comp(c)
{
}

template <class Key, class T, class Compare>
bool multimap<Key, T, Compare>::value_compare::operator()(const value_type &x, const value_type &y) const
{
    return comp(x.first, y.first);
}

template <class Key, class T, class Compare>
multimap<Key, T, Compare>::multimap(const key_compare &comp) : comp(comp), tree(value_compare(comp))
{
}

template <class Key, class T, class Compare>
template <class InputIterator>
multimap<Key, T, Compare>::multimap(InputIterator first, InputIterator last, const key_compare &comp) : tree(first, last, value_compare(comp))
{
}

template <class Key, class T, class Compare>
multimap<Key, T, Compare>::multimap(const multimap &src) : tree(src.tree)
{
}

template <class Key, class T, class Compare>
multimap<Key, T, Compare>::~multimap()
{
}

template <class Key, class T, class Compare>
multimap<Key, T, Compare> &multimap<Key, T, Compare>::operator=(const multimap<Key, T, Compare> &rhs)
{
    if (this != &rhs)
        tree.operator=(rhs.tree);
    return (*this);
};

// Iterators

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::iterator multimap<Key, T, Compare>::begin()
{
    return tree.begin();
}

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::const_iterator multimap<Key, T, Compare>::begin() const
{
    return tree.begin();
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::iterator multimap<Key, T, Compare>::end()
{
    return tree.end();
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::const_iterator multimap<Key, T, Compare>::end() const
{
    return tree.end();
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::reverse_iterator multimap<Key, T, Compare>::rbegin()
{
    return tree.rbegin();
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::const_reverse_iterator multimap<Key, T, Compare>::rbegin() const
{
    return tree.rbegin();
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::reverse_iterator multimap<Key, T, Compare>::rend()
{
    return tree.rend();
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::const_reverse_iterator multimap<Key, T, Compare>::rend() const
{
    return tree.rend();
}

// Capacity

template <class Key, class T, class Compare>
bool multimap<Key, T, Compare>::empty() const
{
    return tree.empty();
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::size_type multimap<Key, T, Compare>::size() const
{
    return tree.size();
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::size_type multimap<Key, T, Compare>::max_size() const
{
    return std::numeric_limits<difference_type>::max();
}

// Modifiers

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::iterator multimap<Key, T, Compare>::insert(const value_type &val)
{
    return tree.insert(val);
}

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::iterator multimap<Key, T, Compare>::insert(iterator position, const value_type &val)
{
    return tree.insert(position, val);
}

template <class Key, class T, class Compare>
template <class InputIterator>
void multimap<Key, T, Compare>::insert(InputIterator first, InputIterator last)
{
    tree.insert(first, last);
}

template <class Key, class T, class Compare>
void multimap<Key, T, Compare>::erase(iterator position)
{
    tree.erase(position);
}

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::size_type multimap<Key, T, Compare>::erase(const key_type &k)
{
    return tree.eraseIf(keysAreTheSame, ft::make_pair<key_type, mapped_type>(k, mapped_type()));
}

template <class Key, class T, class Compare>
void multimap<Key, T, Compare>::erase(iterator first, iterator last)
{
    tree.erase(first, last);
}

template <class Key, class T, class Compare>
void multimap<Key, T, Compare>::swap(multimap &x)
{
    tree.swap(x.tree);
}

template <class Key, class T, class Compare>
void multimap<Key, T, Compare>::clear()
{
    tree.clear();
}

// Observers

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::key_compare multimap<Key, T, Compare>::key_comp() const
{
    return key_compare();
}

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::value_compare multimap<Key, T, Compare>::value_comp() const
{
    return value_compare(Compare());
}

// Operations

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::iterator multimap<Key, T, Compare>::find(const key_type &k)
{
    return tree.find(keysAreTheSame, ft::make_pair<key_type, mapped_type>(k, mapped_type()));
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::const_iterator multimap<Key, T, Compare>::find(const key_type &k) const
{
    return tree.find(keysAreTheSame, ft::make_pair<key_type, mapped_type>(k, mapped_type()));
}

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::size_type multimap<Key, T, Compare>::count(const key_type &k) const
{
    return tree.countIf(keysAreTheSame, ft::make_pair<key_type, mapped_type>(k, mapped_type()));
}

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::iterator multimap<Key, T, Compare>::lower_bound(const key_type &k)
{
    return tree.find(keyIsGreaterOrEqual, ft::make_pair<key_type, mapped_type>(k, mapped_type()));
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::const_iterator multimap<Key, T, Compare>::lower_bound(const key_type &k) const
{
    return tree.find(keyIsGreaterOrEqual, ft::make_pair<key_type, mapped_type>(k, mapped_type()));
}

template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::iterator multimap<Key, T, Compare>::upper_bound(const key_type &k)
{
    return tree.find(keyIsSmaller, ft::make_pair<key_type, mapped_type>(k, mapped_type()));
}
template <class Key, class T, class Compare>
typename multimap<Key, T, Compare>::const_iterator multimap<Key, T, Compare>::upper_bound(const key_type &k) const
{
    return tree.find(keyIsSmaller, ft::make_pair<key_type, mapped_type>(k, mapped_type()));
}

template <class Key, class T, class Compare>
ft::Pair<typename multimap<Key, T, Compare>::const_iterator, typename multimap<Key, T, Compare>::const_iterator> multimap<Key, T, Compare>::equal_range(const key_type &k) const
{
    return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
}
template <class Key, class T, class Compare>
ft::Pair<typename multimap<Key, T, Compare>::iterator, typename multimap<Key, T, Compare>::iterator> multimap<Key, T, Compare>::equal_range(const key_type &k)
{
    return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
}

} // namespace ft

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTreeIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 12:36:18 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 15:00:07 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_ITERATOR
#define RED_BLACK_TREE_ITERATOR

#include "./TreeNode.hpp"
#include "./IteratorTypes.hpp"
#include "RedBlackTree.hpp"

namespace ft
{

    template <class T, class Compare, bool allowDuplicates>
    class RedBlackTree;

    template <class T, class Compare, bool allowDuplicates>
    class RedBlackTreeIterator
    {
    public:
        typedef ft::TreeNode<T> node;

        RedBlackTreeIterator(void);
        RedBlackTreeIterator(const RedBlackTreeIterator &src);
        ~RedBlackTreeIterator();
        RedBlackTreeIterator &operator=(const RedBlackTreeIterator &rhs);

        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef ft::bidirectional_iterator_tag iterator_category;

        reference operator*(void) const;
        pointer operator->(void) const;
        RedBlackTreeIterator &operator++();
        RedBlackTreeIterator &operator--();
        RedBlackTreeIterator operator++(int dummy);
        RedBlackTreeIterator operator--(int dummy);

        bool operator==(const RedBlackTreeIterator &rhs) const;
        bool operator!=(const RedBlackTreeIterator &rhs) const;

        RedBlackTreeIterator(node *ptr, node *tNull, node *min, node *max);
        node *ptr;

    private:
        bool isLeafNode(node *e);

        node *tNull;
        node *min;
        node *max;
    };

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates>::RedBlackTreeIterator(void){

    };

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates>::RedBlackTreeIterator(node *ptr, node *tNull, node *min, node *max) : ptr(ptr), tNull(tNull), min(min), max(max){};

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates>::RedBlackTreeIterator(const RedBlackTreeIterator &src) : ptr(src.ptr), tNull(src.tNull), min(src.min), max(src.max){};

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates>::~RedBlackTreeIterator(){

    };

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates> &RedBlackTreeIterator<T, Compare, allowDuplicates>::operator=(const RedBlackTreeIterator &rhs)
    {
        if (this != &rhs)
        {
            this->ptr = rhs.ptr;
            this->tNull = rhs.tNull;
            this->min = rhs.min;
            this->max = rhs.max;
        }
        return (*this);
    };

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTreeIterator<T, Compare, allowDuplicates>::reference RedBlackTreeIterator<T, Compare, allowDuplicates>::operator*(void) const
    {
        return this->ptr->data;
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTreeIterator<T, Compare, allowDuplicates>::pointer RedBlackTreeIterator<T, Compare, allowDuplicates>::operator->(void) const
    {
        return &this->ptr->data;
    }

    template <class T, class Compare, bool allowDuplicates>
    bool RedBlackTreeIterator<T, Compare, allowDuplicates>::isLeafNode(node *e)
    {
        return (e == tNull);
    }

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates> &RedBlackTreeIterator<T, Compare, allowDuplicates>::operator++()
    {
        if (!ptr || isLeafNode(ptr))
            ptr = min;
        else if (!isLeafNode(ptr->right))
        {
            ptr = ptr->right;
            while (!isLeafNode(ptr) && !isLeafNode(ptr->left))
                ptr = ptr->left;
        }
        else
        {
            node *tmp;
            do
            {
                tmp = ptr;
                ptr = ptr->parent;
            } while (!isLeafNode(ptr) && tmp == ptr->right);
        }
        return (*this);
    }

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates> &RedBlackTreeIterator<T, Compare, allowDuplicates>::operator--()
    {
        if (!ptr || isLeafNode(ptr))
            ptr = max;
        else if (!isLeafNode(ptr->left))
        {
            ptr = ptr->left;
            while (!isLeafNode(ptr) && !isLeafNode(ptr->right))
            {
                ptr = ptr->right;
            }
        }
        else
        {
            node *tmp;
            do
            {
                tmp = ptr;
                ptr = ptr->parent;
            } while (!isLeafNode(ptr) && tmp == ptr->left);
        }
        return (*this);
    }

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates> RedBlackTreeIterator<T, Compare, allowDuplicates>::operator++(int dummy)
    {
        (void)dummy;
        RedBlackTreeIterator<T, Compare, allowDuplicates> copy = *this;
        ++(*this);
        return (copy);
    }

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTreeIterator<T, Compare, allowDuplicates> RedBlackTreeIterator<T, Compare, allowDuplicates>::operator--(int dummy)
    {
        (void)dummy;
        RedBlackTreeIterator<T, Compare, allowDuplicates> copy = *this;
        --(*this);
        return (copy);
    }

    template <class T, class Compare, bool allowDuplicates>
    bool RedBlackTreeIterator<T, Compare, allowDuplicates>::operator==(const RedBlackTreeIterator &rhs) const
    {
        return this->ptr == rhs.ptr;
    }

    template <class T, class Compare, bool allowDuplicates>
    bool RedBlackTreeIterator<T, Compare, allowDuplicates>::operator!=(const RedBlackTreeIterator &rhs) const
    {
        return this->ptr != rhs.ptr;
    }
} // namespace ft

#endif

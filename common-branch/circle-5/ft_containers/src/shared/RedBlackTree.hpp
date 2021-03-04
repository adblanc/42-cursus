/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:17:26 by adrien            #+#    #+#             */
/*   Updated: 2020/10/24 14:56:58 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <stdlib.h>
#include "TreeNode.hpp"
#include "RedBlackTreeIterator.hpp"
#include "../shared/ReverseBiDirIter.hpp"

namespace ft
{

    template <class T, class Compare, bool allowDuplicates>
    class RedBlackTree
    {
    public:
        typedef TreeNode<T> *nodePtr;
        typedef TreeNode<const T> *const_nodePtr;
        typedef RedBlackTreeIterator<T, Compare, allowDuplicates> iterator;
        typedef RedBlackTreeIterator<const T, Compare, allowDuplicates> const_iterator;
        typedef ReverseBiDirIter<iterator> reverse_iterator;
        typedef ReverseBiDirIter<const_iterator> const_reverse_iterator;

        explicit RedBlackTree(const Compare &comp = Compare());
        template <class InputIterator>
        RedBlackTree(InputIterator first, InputIterator last, const Compare &comp = Compare());
        RedBlackTree(const RedBlackTree &src);
        ~RedBlackTree();

        RedBlackTree &operator=(const RedBlackTree &rhs);

        iterator insert(const T &data);
        iterator insert(iterator position, const T &data);
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last);

        void erase(iterator position);
        void erase(iterator first, iterator last);
        template <typename Predicate>
        size_t eraseIf(Predicate pred, const T &data);

        void swap(RedBlackTree<T, Compare, allowDuplicates> &x);

        template <typename Predicate>
        iterator find(Predicate pred, const T &data);
        template <typename Predicate>
        const_iterator find(Predicate pred, const T &data) const;

        template <typename Predicate>
        size_t countIf(Predicate pred, const T &data) const;

        void clear();

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
        size_t size() const;

    private:
        nodePtr getParent(nodePtr n);
        nodePtr getGrandParent(nodePtr n);
        nodePtr getSibling(nodePtr n);
        nodePtr getUncle(nodePtr n);

        nodePtr minimum() const;
        nodePtr maximum() const;

        nodePtr minimum(nodePtr n) const;
        nodePtr maximum(nodePtr n) const;

        void rotateLeft(nodePtr n);
        void rotateRight(nodePtr n);

        nodePtr createNewNodeToAdd(const T &data, nodePtr parent);

        iterator insertFrom(nodePtr recRoot, const T &data);
        iterator insertRecurse(nodePtr recRoot, const T &data);
        void insertRepair(nodePtr n);
        void insertCase1(nodePtr n);
        void insertCase2(nodePtr n);
        void insertCase3(nodePtr n);
        void insertCase4(nodePtr n);
        void insertCase4Step2(nodePtr n);

        void replaceNode(nodePtr n, nodePtr child);

        void deleteNode(nodePtr node);
        void deleteFix(nodePtr x);

        void clear(nodePtr root);

        void deepCopy(nodePtr srcRoot, nodePtr srcTNull);

        template <typename Predicate>
        size_t countIfRec(nodePtr recRoot, Predicate pred, const T &data) const;

        nodePtr root;
        nodePtr tNull;
        size_t length;
        Compare cmp;
    };

    template <class T, class Compare, bool allowDuplicates>
    template <class InputIterator>
    RedBlackTree<T, Compare, allowDuplicates>::RedBlackTree(InputIterator first, InputIterator last, const Compare &comp) : length(0), cmp(comp)
    {
        tNull = new TreeNode<T>;
        root = tNull;
        insert(first, last);
    }

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTree<T, Compare, allowDuplicates>::RedBlackTree(const Compare &comp) : length(0), cmp(comp)
    {
        tNull = new TreeNode<T>;
        root = tNull;
    }

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTree<T, Compare, allowDuplicates> &RedBlackTree<T, Compare, allowDuplicates>::operator=(const RedBlackTree &rhs)
    {
        if (this != &rhs)
        {
            clear();
            deepCopy(rhs.root, rhs.tNull);
        }
        return (*this);
    }

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTree<T, Compare, allowDuplicates>::RedBlackTree(const RedBlackTree &src) : length(0), cmp(src.cmp)
    {
        tNull = new TreeNode<T>;
        root = tNull;
        deepCopy(src.root, src.tNull);
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::deepCopy(nodePtr srcRoot, nodePtr srcTnull)
    {
        if (!srcRoot || srcRoot == srcTnull)
            return;
        deepCopy(srcRoot->left, srcTnull);
        insert(srcRoot->data);
        deepCopy(srcRoot->right, srcTnull);
    }

    template <class T, class Compare, bool allowDuplicates>
    RedBlackTree<T, Compare, allowDuplicates>::~RedBlackTree()
    {
        clear();
        delete tNull;
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::iterator RedBlackTree<T, Compare, allowDuplicates>::begin()
    {
        nodePtr min = minimum();
        return iterator(min, this->tNull, min, maximum());
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::const_iterator RedBlackTree<T, Compare, allowDuplicates>::begin() const
    {
        const_nodePtr min = reinterpret_cast<const_nodePtr>(minimum());
        const_nodePtr max = reinterpret_cast<const_nodePtr>(maximum());
        const_nodePtr tNull = reinterpret_cast<const_nodePtr>(this->tNull);
        return const_iterator(min, tNull, min, max);
    }
    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::iterator RedBlackTree<T, Compare, allowDuplicates>::end()
    {
        nodePtr max = maximum();
        return ++iterator(max, this->tNull, minimum(), max);
    }
    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::const_iterator RedBlackTree<T, Compare, allowDuplicates>::end() const
    {
        const_nodePtr min = reinterpret_cast<const_nodePtr>(minimum());
        const_nodePtr max = reinterpret_cast<const_nodePtr>(maximum());
        const_nodePtr tNull = reinterpret_cast<const_nodePtr>(this->tNull);
        return ++const_iterator(max, tNull, min, max);
    }
    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::reverse_iterator RedBlackTree<T, Compare, allowDuplicates>::rbegin()
    {
        return reverse_iterator(end());
    }
    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::const_reverse_iterator RedBlackTree<T, Compare, allowDuplicates>::rbegin() const
    {
        return const_reverse_iterator(end());
    }
    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::reverse_iterator RedBlackTree<T, Compare, allowDuplicates>::rend()
    {
        return reverse_iterator(begin());
    }
    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::const_reverse_iterator RedBlackTree<T, Compare, allowDuplicates>::rend() const
    {
        return const_reverse_iterator(begin());
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::getParent(nodePtr n)
    {
        return n == NULL ? NULL : n->parent;
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::getGrandParent(nodePtr n)
    {
        return getParent(getParent(n));
    }

    template <class T, class Compare, bool allowDuplicates>
    bool RedBlackTree<T, Compare, allowDuplicates>::empty() const
    {
        return (size() == 0);
    }

    template <class T, class Compare, bool allowDuplicates>
    size_t RedBlackTree<T, Compare, allowDuplicates>::size() const
    {
        return length;
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::getSibling(nodePtr n)
    {
        nodePtr parent = getParent(n);

        if (!parent)
            return NULL;

        if (parent->left == n)
            return parent->right;

        return parent->left;
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::getUncle(nodePtr n)
    {
        nodePtr parent = getParent(n);

        return getSibling(parent);
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::rotateLeft(nodePtr x)
    {
        nodePtr y = x->right;

        x->right = y->left;
        if (y->left != tNull)
            y->left->parent = x;
        y->parent = getParent(x);
        if (getParent(x) == NULL || getParent(x) == tNull)
            root = y;
        else if (x == getParent(x)->left)
            getParent(x)->left = y;
        else
            getParent(x)->right = y;
        y->left = x;
        x->parent = y;
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::rotateRight(nodePtr x)
    {
        nodePtr y = x->left;
        x->left = y->right;

        if (y->right != tNull)
            y->right->parent = x;
        y->parent = x->parent;
        if (getParent(x) == NULL || getParent(x) == tNull)
            root = y;
        else if (getParent(x)->right == x)
            getParent(x)->right = y;
        else
            getParent(x)->left = y;
        y->right = x;
        x->parent = y;
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::clear()
    {
        while (!empty())
            erase(begin());
    }

    template <class T, class Compare, bool allowDuplicates>
    template <class InputIterator>
    void RedBlackTree<T, Compare, allowDuplicates>::insert(InputIterator first, InputIterator last)
    {
        for (InputIterator it = first; it != last; it++)
            insert(*it);
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::iterator RedBlackTree<T, Compare, allowDuplicates>::insert(const T &data)
    {
        return insertFrom(root, data);
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::iterator RedBlackTree<T, Compare, allowDuplicates>::insert(iterator position, const T &data)
    {
        (void)position;
        return insertFrom(root, data);
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::iterator RedBlackTree<T, Compare, allowDuplicates>::insertFrom(nodePtr recRoot, const T &data)
    {
        iterator it = insertRecurse(recRoot, data);

        insertRepair(it.ptr);

        recRoot = it.ptr;
        while (getParent(recRoot) && getParent(recRoot) != tNull)
            recRoot = getParent(recRoot);

        this->root = recRoot;

        return it;
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::iterator RedBlackTree<T, Compare, allowDuplicates>::insertRecurse(nodePtr recRoot, const T &data)
    {
        if (recRoot != NULL && recRoot != tNull)
        {
            if (cmp(data, recRoot->data))
            {
                if (recRoot->left != tNull)
                    return insertRecurse(recRoot->left, data);
                else
                {
                    recRoot->left = createNewNodeToAdd(data, recRoot);
                    return iterator(recRoot->left, tNull, minimum(), maximum());
                }
            }
            else if (cmp(recRoot->data, data) || allowDuplicates)
            {
                if (recRoot->right != tNull)
                    return insertRecurse(recRoot->right, data);
                else
                {
                    recRoot->right = createNewNodeToAdd(data, recRoot);
                    return iterator(recRoot->right, tNull, minimum(), maximum());
                }
            }
            else
            {
                return iterator(recRoot, tNull, minimum(), maximum());
            }
        }
        else
            return iterator(createNewNodeToAdd(data, recRoot), tNull, minimum(), maximum());
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::createNewNodeToAdd(const T &data, nodePtr parent)
    {
        length++;
        return new TreeNode<T>(data, red, tNull, tNull, parent);
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::insertRepair(nodePtr n)
    {
        if (getParent(n) == NULL || getParent(n) == tNull)
            insertCase1(n);
        else if (getParent(n)->color == black)
            insertCase2(n);
        else if (getUncle(n) != NULL && getUncle(n)->color == red)
            insertCase3(n);
        else
            insertCase4(n);
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::insertCase1(nodePtr n)
    {
        n->color = black;
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::insertCase2(nodePtr n)
    {
        (void)n;
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::insertCase3(nodePtr n)
    {
        getParent(n)->color = black;
        getUncle(n)->color = black;
        getGrandParent(n)->color = red;
        insertRepair(getGrandParent(n)); // repair if gp === root
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::insertCase4(nodePtr n)
    {
        nodePtr parent = getParent(n);
        nodePtr grandParent = getGrandParent(n);

        if (n == parent->right && parent == grandParent->left)
        {
            rotateLeft(parent);
            n = n->left;
        }
        else if (n == parent->left && parent == grandParent->right)
        {
            rotateRight(parent);
            n = n->right;
        }
        insertCase4Step2(n);
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::insertCase4Step2(nodePtr n)
    {
        nodePtr parent = getParent(n);
        nodePtr grandParent = getGrandParent(n);

        if (n == parent->left)
            rotateRight(grandParent);
        else
            rotateLeft(grandParent);

        parent->color = black;
        grandParent->color = red;
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::replaceNode(nodePtr u, nodePtr v)
    {
        if (u->parent == NULL || u->parent == tNull)
            root = v;
        else if (u == getParent(u)->left)
            getParent(u)->left = v;
        else
            getParent(u)->right = v;

        v->parent = u->parent;
    }

    template <class T, class Compare, bool allowDuplicates>
    template <typename Predicate>
    size_t RedBlackTree<T, Compare, allowDuplicates>::eraseIf(Predicate pred, const T &data)
    {
        (void)pred;
        nodePtr node;
        size_t initalLength = size();

        node = this->root;
        while (node && node != tNull)
        {
            if (pred(node->data, data))
            {
                deleteNode(node);
                node = this->root;
            }
            else if (cmp(data, node->data))
                node = node->left;
            else if (cmp(node->data, data))
                node = node->right;
        }
        return initalLength - size();
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::erase(iterator first, iterator last)
    {
        iterator it = first;

        while (it != last)
            erase(it++);
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::erase(iterator position)
    {
        return deleteNode(position.ptr);
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::deleteNode(nodePtr node)
    {
        nodePtr x, y = NULL;
        nodePtr toDelete = node;

        if (toDelete == NULL || toDelete == tNull)
            return;

        y = toDelete;
        t_colors originalColor = toDelete->color;

        if (toDelete->left == tNull)
        {
            x = toDelete->right;
            replaceNode(toDelete, toDelete->right);
        }
        else if (toDelete->right == tNull)
        {
            x = toDelete->left;
            replaceNode(toDelete, toDelete->left);
        }
        else
        {
            y = minimum(toDelete->right);
            originalColor = y->color;
            x = y->right;
            if (getParent(y) == toDelete)
                x->parent = y;
            else
            {
                replaceNode(y, y->right);
                y->right = toDelete->right;
                y->right->parent = y;
            }
            replaceNode(toDelete, y);
            y->left = toDelete->left;
            y->left->parent = y;
            y->color = toDelete->color;
        }
        delete toDelete;
        length--;
        if (originalColor == black)
            deleteFix(x);
    }

    template <class T, class Compare, bool allowDuplicates>
    template <typename Predicate>
    typename RedBlackTree<T, Compare, allowDuplicates>::iterator RedBlackTree<T, Compare, allowDuplicates>::find(Predicate pred, const T &data)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            if (pred(data, *it))
                return it;
        }
        return end();
    }

    template <class T, class Compare, bool allowDuplicates>
    template <typename Predicate>
    typename RedBlackTree<T, Compare, allowDuplicates>::const_iterator RedBlackTree<T, Compare, allowDuplicates>::find(Predicate pred, const T &data) const
    {
        for (const_iterator it = begin(); it != end(); it++)
        {
            if (pred(data, *it))
                return it;
        }
        return end();
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::deleteFix(nodePtr x)
    {
        nodePtr s;
        while (x != root && x->color == black)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == red)
                {
                    s->color = black;
                    x->parent->color = red;
                    rotateLeft(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == black && s->right->color == black)
                {
                    s->color = red;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == black)
                    {
                        s->left->color = black;
                        s->color = red;
                        rotateRight(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = black;
                    s->right->color = black;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == red)
                {
                    s->color = black;
                    x->parent->color = red;
                    rotateRight(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == black && s->right->color == black)
                {
                    s->color = red;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == black)
                    {
                        s->right->color = black;
                        s->color = red;
                        rotateLeft(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = black;
                    s->left->color = black;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = black;
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::minimum() const
    {
        return minimum(this->root);
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::minimum(nodePtr n) const
    {
        if (!n || n == tNull)
            return NULL;
        while (n->left != tNull)
            n = n->left;
        return n;
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::maximum() const
    {
        return maximum(this->root);
    }

    template <class T, class Compare, bool allowDuplicates>
    typename RedBlackTree<T, Compare, allowDuplicates>::nodePtr RedBlackTree<T, Compare, allowDuplicates>::maximum(nodePtr n) const
    {
        if (!n || n == tNull)
            return NULL;
        while (n->right != tNull)
            n = n->right;
        return n;
    }

    template <class T, class Compare, bool allowDuplicates>
    template <typename Predicate>
    size_t RedBlackTree<T, Compare, allowDuplicates>::countIf(Predicate pred, const T &data) const
    {
        return countIfRec(this->root, pred, data);
    }

    template <class T, class Compare, bool allowDuplicates>
    template <typename Predicate>
    size_t RedBlackTree<T, Compare, allowDuplicates>::countIfRec(nodePtr recRoot, Predicate pred, const T &data) const
    {
        size_t count = 0;
        if (!recRoot || recRoot == tNull)
            return 0;
        count += countIfRec(recRoot->left, pred, data);
        count += countIfRec(recRoot->right, pred, data);

        if (pred(data, recRoot->data))
            count++;
        return count;
    }

    template <class T, class Compare, bool allowDuplicates>
    void RedBlackTree<T, Compare, allowDuplicates>::swap(RedBlackTree<T, Compare, allowDuplicates> &x)
    {
        nodePtr tmp_root = root;
        nodePtr tmp_tNull = tNull;
        size_t tmp_length = size();

        root = x.root;
        tNull = x.tNull;
        length = x.length;

        x.root = tmp_root;
        x.tNull = tmp_tNull;
        x.length = tmp_length;
    }

} // namespace ft

#endif

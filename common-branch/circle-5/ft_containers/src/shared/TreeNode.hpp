/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeNode.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:12:34 by adrien            #+#    #+#             */
/*   Updated: 2020/04/17 12:29:01 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

namespace ft
{
typedef enum e_colors
{
    black,
    red
} t_colors;

template <typename T>
class TreeNode
{
public:
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode(void);
    TreeNode(const T &data, t_colors color, TreeNode<T> *left = NULL, TreeNode<T> *right = NULL,
             TreeNode<T> *parent = NULL);
    ~TreeNode();
    TreeNode(const TreeNode<T> &src);
    TreeNode<T> &operator=(const TreeNode<T> &rhs);

    T data;
    t_colors color;
};

template <typename T>
TreeNode<T>::TreeNode(void) : left(NULL), right(NULL), parent(NULL), data(), color(black)
{
}

template <typename T>
TreeNode<T>::TreeNode(const T &data, t_colors color, TreeNode<T> *left, TreeNode<T> *right,
                      TreeNode<T> *parent) : left(left), right(right), parent(parent), data(data), color(color)
{
}

template <typename T>
TreeNode<T>::TreeNode(const TreeNode<T> &src) : left(src.left), right(src.right), parent(src.parent), data(src.data), color(src.color)
{
}

template <typename T>
TreeNode<T>::~TreeNode()
{
}

template <typename T>
TreeNode<T> &TreeNode<T>::operator=(const TreeNode<T> &rhs)
{
    if (this != &rhs)
    {
        left = rhs.left;
        right = rhs.right;
        parent = rhs.parent;
        data = rhs.data;
        color = rhs.color;
    }
    return (*this);
}

} // namespace ft

#endif

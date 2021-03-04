/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:58:04 by adrien            #+#    #+#             */
/*   Updated: 2020/03/11 11:19:21 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutantstack.hpp"
#include <iostream>

int main()
{
    if (true)
    {

        MutantStack<int> mstack;

        std::cout << "=== MutantStack ===" << std::endl;

        std::cout << "Push 5" << std::endl;
        mstack.push(5);
        std::cout << "Push 17" << std::endl;
        mstack.push(17);

        std::cout << "Element on the top : " << std::endl;
        std::cout << mstack.top() << std::endl;

        std::cout << "We pop an element." << std::endl;
        mstack.pop();

        std::cout << "Size : ";
        std::cout << mstack.size() << std::endl;

        std::cout << "Push 3" << std::endl;
        mstack.push(3);
        std::cout << "Push 5" << std::endl;
        mstack.push(5);
        std::cout << "Push 737" << std::endl;
        mstack.push(737);

        std::cout << "Push 0" << std::endl;
        mstack.push(0);

        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();

        ++it;
        --it;

        std::cout << "We display the whole stack." << std::endl;

        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }

        std::stack<int> s(mstack);

        std::cout << "We copy our mutantStack" << std::endl;
        MutantStack<int> copy(mstack);

        std::cout << "Copy size : ";
        std::cout << copy.size() << std::endl;

        std::cout << "Original size : ";
        std::cout << mstack.size() << std::endl;

        std::cout << "We assign our original to another copy using = operator" << std::endl;
        MutantStack<int> test = mstack;

        std::cout << "another copy size : ";
        std::cout << test.size() << std::endl;

        std::cout << "Original size :";
        std::cout << mstack.size() << std::endl;
    }
    if (true)
    {

        std::cout << std::endl
                  << "=== List ===" << std::endl;

        std::list<int> mstack;

        std::cout << "Push 5" << std::endl;
        mstack.push_back(5);
        std::cout << "Push 17" << std::endl;
        mstack.push_back(17);

        std::cout << "Element on the top : " << std::endl;
        std::cout << mstack.back() << std::endl;

        std::cout << "We pop an element." << std::endl;
        mstack.pop_back();

        std::cout << "Size : ";
        std::cout << mstack.size() << std::endl;

        std::cout << "Push 3" << std::endl;
        mstack.push_back(3);
        std::cout << "Push 5" << std::endl;
        mstack.push_back(5);
        std::cout << "Push 737" << std::endl;
        mstack.push_back(737);

        std::cout << "Push 0" << std::endl;
        mstack.push_back(0);

        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();

        ++it;
        --it;

        std::cout << "We display the whole list." << std::endl;

        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }

        std::list<int> s(mstack);

        std::cout << "We copy our list" << std::endl;
        std::list<int> copy(mstack);

        std::cout << "Copy size : ";
        std::cout << copy.size() << std::endl;

        std::cout << "Original size :";
        std::cout << mstack.size() << std::endl;

        std::cout << "We assign our original to another copy using = operator" << std::endl;
        std::list<int> test = mstack;

        std::cout << "another copy size : ";
        std::cout << test.size() << std::endl;

        std::cout << "Original size : ";
        std::cout << mstack.size() << std::endl;
    }
    return (0);
}

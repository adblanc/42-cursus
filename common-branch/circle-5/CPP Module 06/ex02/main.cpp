/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:30:18 by adrien            #+#    #+#             */
/*   Updated: 2020/03/09 14:21:48 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "iostream"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int randomInt(int min, int max)
{
    return (std::rand() % (max - min + 1) + 1);
}

Base *generate(void)
{
    int random = randomInt(1, 3);
    if (random == 1)
        return (new A());
    if (random == 2)
        return (new B());
    return new C();
}

void identify_from_pointer(Base *p)
{
    if (A *ptr_1 = dynamic_cast<A *>(p))
    {
        static_cast<void>(ptr_1);
        std::cout << "A" << std::endl;
    }
    else if (B *ptr_2 = dynamic_cast<B *>(p))
    {
        static_cast<void>(ptr_2);
        std::cout << "B" << std::endl;
    }
    else if (C *ptr_3 = dynamic_cast<C *>(p))
    {
        static_cast<void>(ptr_3);
        std::cout << "C" << std::endl;
    }
}

void identify_from_reference(Base &p)
{
    try
    {
        A &a = dynamic_cast<A &>(p);
        static_cast<void>(a);
        std::cout << "A" << std::endl;
    }
    catch (std::bad_cast &e)
    {
        try
        {
            B &b = dynamic_cast<B &>(p);
            static_cast<void>(b);
            std::cout << "B" << std::endl;
        }
        catch (std::bad_cast &e)
        {
            try
            {
                C &c = dynamic_cast<C &>(p);
                static_cast<void>(c);
                std::cout << "C" << std::endl;
            }
            catch (std::bad_cast &e)
            {
                std::cout << "Could not process type" << std::endl;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    A *a = new A();
    B *b = new B();
    C *c = new C();

    Base *pt_1 = generate();
    Base *pt_2 = generate();
    Base *pt_3 = generate();

    identify_from_pointer(a);
    identify_from_pointer(b);
    identify_from_pointer(c);

    identify_from_reference(*a);
    identify_from_reference(*b);
    identify_from_reference(*c);

    identify_from_pointer(pt_1);
    identify_from_pointer(pt_2);
    identify_from_pointer(pt_3);

    identify_from_reference(*pt_1);
    identify_from_reference(*pt_2);
    identify_from_reference(*pt_3);

    delete a;
    delete b;
    delete c;

    delete pt_1;
    delete pt_2;
    delete pt_3;

    return (0);
}

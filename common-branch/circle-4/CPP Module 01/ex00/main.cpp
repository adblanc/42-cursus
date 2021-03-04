/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:24:18 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 15:56:02 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pony.hpp"
#include <iostream>

void	ponyOnTheHeap()
{
	Pony *myPoney;

	myPoney = new Pony;
	myPoney->bringToLife();
	myPoney->setAge(3);
	myPoney->setSpeed(20);

	delete myPoney;
}

void	ponyOnTheStack()
{
	Pony myPoney;

	myPoney.bringToLife();
	myPoney.setAge(3);
	myPoney.setSpeed(20);
}

int main()
{
	ponyOnTheHeap();
	ponyOnTheStack();
	std::cout << "Stack declaration memory is cleaned up automaticcaly after the return of the function" << std::endl;
	std::cout << "Heap memory is allocated using the new keyword and is cleaned using the delete keyword" << std::endl;
	return (0);
}

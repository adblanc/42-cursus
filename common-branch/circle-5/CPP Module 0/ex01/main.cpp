/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:25:26 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 15:14:59 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

static bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int			get_index(int counter)
{
	std::string	input;
	int			index;

	while (1) {
	std::getline(std::cin, input);
	std::stringstream ss(input);
	ss >> index;
	if (index < 0 || index >= counter || !is_number(input))
	{
		std::cout << "Bad index, please enter a valid one" << std::endl;
	}
	else
		break;
	}
	return (index);
}

void	displayHeader()
{
	std::cout <<  std::setw(10) << "index" << "|";
	std::cout <<  std::setw(10) << "first name" << "|";
	std::cout <<  std::setw(10) << "last name" << "|";
	std::cout <<  std::setw(10) << "login" << std::endl;
}

bool displayContactList(Contact contacts[8], int counter)
{
	int					i;
	std::stringstream	ss;
	std::string			field;

	if (!counter)
	{
		std::cout << "There is no contact in your list !";
		return (0);
	}

	i = -1;
	std::cout << std::setw(10);
	displayHeader();
	while (++i < counter)
		contacts[i].displayTable(i);

	return (1);
}

int main()
{
	std::string	input;
	int			counter;
	Contact		contacts[8];

	counter = 0;
	std::cout << "Hi, welcome to ANNUL, please enter one of the following command : " << std::endl;
	std::cout << "=====" << std::endl;
	std::cout << "ADD" << std::endl << "SEARCH" << std::endl << "EXIT" << std::endl;
	std::cout << "=====" << std::endl;
	while (1)
	{
		std::getline(std::cin, input);
		if (input == "ADD")
		{
			if (counter >= 8)
				std::cout << "Can't add more than 8 contacts !";
			else
				contacts[counter++].displayForm();
		}
		else if (input == "SEARCH")
		{
			if (displayContactList(contacts, counter)) {
				std::cout << "Please enter the index of the contact u want to know more about" << std::endl;
				contacts[get_index(counter)].displayMoreInformation();
		}
		}
		else if (input == "EXIT")
			break ;
		else
			std::cout << "Please enter a valid command";
		std::cout << std::endl;
	}
	return (0);
}

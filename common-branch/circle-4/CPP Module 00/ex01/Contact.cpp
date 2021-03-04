/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 10:50:38 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 13:23:36 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"


static void	displayField(std::string field)
{
	if (field.length() > 10)
	{
		field[9] = '.';
		field.resize(10);
	}
	std::cout << std::setw(10) << field;
}

Contact::Contact(void) {
	this->firstName = "";
	this->lastName = "";
	this->nickName = "";
	this->login = "";
	this->postalAddress = "";
	this->emailAddress = "";
	this->phoneNumber = "";
	this->birthdayDate = "";
	this->favoriteMeal = "";
	this->underwearColor = "";
	this->darkestSecret = "";
}

void	Contact::displayForm(void)
{
	std::string input;

	std::cout << "Please specify " << "first name" << std::endl;
	std::getline(std::cin, input);
	this->firstName = input;	

	std::cout << "Please specify " << "last name" << std::endl;
	std::getline(std::cin, input);
	this->lastName = input;	

	std::cout << "Please specify " << "nickname" << std::endl;
	std::getline(std::cin, input);
	this->nickName = input;	

	std::cout << "Please specify " << "login" << std::endl;
	std::getline(std::cin, input);
	this->login = input;	

	std::cout << "Please specify " << "postal address" << std::endl;
	std::getline(std::cin, input);
	this->postalAddress = input;	

	std::cout << "Please specify " << "email address" << std::endl;
	std::getline(std::cin, input);
	this->emailAddress= input;	

	std::cout << "Please specify " << "phone number" << std::endl;
	std::getline(std::cin, input);
	this->phoneNumber = input;	

	std::cout << "Please specify " << "birthday date" << std::endl;
	std::getline(std::cin, input);
	this->birthdayDate = input;	

	std::cout << "Please specify " << "favorite meal" << std::endl;
	std::getline(std::cin, input);
	this->favoriteMeal = input;	

	std::cout << "Please specify " << "underwear color" << std::endl;
	std::getline(std::cin, input);
	this->underwearColor= input;	

	std::cout << "Please specify " << "darkest secret" << std::endl;
	std::getline(std::cin, input);
	this->darkestSecret = input;	

	std::cout << this->lastName + " " + this->firstName + " added.";
}

void	Contact::displayTable(int i)
{
	std::stringstream	ss;
	std::string			field;

	std::cout << std::setw(10);
	ss << i;
	displayField(ss.str());
	std::cout << "|";
	displayField(this->firstName);
	std::cout << "|";
	displayField(this->lastName);
	std::cout << "|";
	displayField(this->login);
	ss.str("");
	ss.clear();
	std::cout << std::endl;

}

void	Contact::displayMoreInformation(void)
{
	std::cout << "First name :" << std::endl;
	std::cout << this->firstName << std::endl;

	std::cout << "Last name :" << std::endl;
	std::cout << this->lastName << std::endl;

	std::cout << "Nickname :" << std::endl;
	std::cout << this->nickName << std::endl;

	std::cout << "Login :" << std::endl;
	std::cout << this->login << std::endl;

	std::cout << "Postal address: " << std::endl;
	std::cout << this->postalAddress << std::endl;

	std::cout << "Email address: " << std::endl;
	std::cout << this->emailAddress << std::endl;

	std::cout << "Phone number: " << std::endl;
	std::cout << this->phoneNumber << std::endl;
	
	std::cout << "Birthday date: " << std::endl;
	std::cout << this->birthdayDate << std::endl;

	std::cout << "Favorite meal: " << std::endl;
	std::cout << this->favoriteMeal << std::endl;

	std::cout << "Underwear color: " << std::endl;
	std::cout << this->underwearColor << std::endl;

	std::cout << "Darkest secret: " << std::endl;
	std::cout << this->darkestSecret;
}

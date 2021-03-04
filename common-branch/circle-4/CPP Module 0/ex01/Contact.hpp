/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:04:47 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 13:21:07 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_H
# define CONTACT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class Contact
{
	public:
	Contact(void);

	void	displayForm(void);
	void	displayTable(int i);
	void	displayMoreInformation(void);

	private:

	std::string	firstName;
	std::string	lastName;
	std::string	nickName;
	std::string	login;
	std::string	postalAddress;
	std::string	emailAddress;
	std::string	phoneNumber;
	std::string	birthdayDate;
	std::string	favoriteMeal;
	std::string	underwearColor;
	std::string	darkestSecret;
};

#endif

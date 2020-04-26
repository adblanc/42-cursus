/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex04.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:52:30 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 14:07:32 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main()
{
	std::string s;
	std::string& s_ref = s;
	char *p;

	s = "HI THIS IS BRAIN";
	p = (char *)s.c_str();

	std::cout << p << std::endl;
	std::cout << s_ref << std::endl;
	return (0);
}

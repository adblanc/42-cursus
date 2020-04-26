/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:46:26 by adrien            #+#    #+#             */
/*   Updated: 2020/01/13 17:38:24 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

int main()
{
    std::cout << "--------------------EX 03---------------------" << std::endl << std::endl;
    Bureaucrat beaugosse("bg", 1);
    Intern randomGuy;

    Form *first;
    Form *second;
    Form *third;
    Form *last;

    first = randomGuy.makeForm("robotomy request", "Bender");
    
    beaugosse.signForm(*first);
    beaugosse.executeForm(*first);

    std::cout << std::endl << std::endl;

    second = randomGuy.makeForm("presidential pardon", "Bendo");
    
    beaugosse.signForm(*second);
    beaugosse.executeForm(*second);

     std::cout << std::endl << std::endl;

    third = randomGuy.makeForm("shruberry creation", "GeorgesBush");
    
    beaugosse.signForm(*third);
    beaugosse.executeForm(*third);

     std::cout << std::endl << std::endl;

    last = randomGuy.makeForm("unknown", "2wg");
    (void)last;

    
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:46:26 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 08:53:51 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

void    executeConcretesForm() {
    try {
    ShrubberyCreationForm shrub("target1");
    PresidentialPardonForm pres("target2");
    RobotomyRequestForm robot("target3");

    Bureaucrat adrien("adrien", 1);

    shrub.beSigned(adrien);
    pres.beSigned(adrien);
    robot.beSigned(adrien);

    adrien.executeForm(shrub);
    adrien.executeForm(pres);
    adrien.executeForm(robot);

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    executeConcretesFormFail() {
    try {
    ShrubberyCreationForm shrub("target1");
    PresidentialPardonForm pres("target2");
    RobotomyRequestForm robot("target3");

    Bureaucrat adrien("adrien", 1);

    adrien.executeForm(shrub);
    adrien.executeForm(pres);
    adrien.executeForm(robot);

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    executeConcretesFormFailAgain() {
    try {
    ShrubberyCreationForm shrub("target1");
    PresidentialPardonForm pres("target2");
    RobotomyRequestForm robot("target3");

    Bureaucrat adrien("adrien", 1);
     Bureaucrat adrienFail("adrienFail", 149);

    shrub.beSigned(adrien);
    pres.beSigned(adrien);
    robot.beSigned(adrien);

    adrienFail.executeForm(shrub);
    adrienFail.executeForm(pres);
    adrienFail.executeForm(robot);

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    signConcretesForm(Form &form, Bureaucrat &bureaucrat) {
    try {
        bureaucrat.signForm(form);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    executeConcretesForm(Form &form, Bureaucrat &bureaucrat) {
    try {
        bureaucrat.executeForm(form);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    testSignatures() {
    Bureaucrat a("a", 146);
    Bureaucrat b("b", 73);
    Bureaucrat c("c", 26);

    Bureaucrat d("d", 145);
    Bureaucrat e("e", 72);
    Bureaucrat f("f", 25);

    ShrubberyCreationForm aForm("target");
    RobotomyRequestForm bForm("target");
    PresidentialPardonForm cForm("target");

    signConcretesForm(aForm, a);
    signConcretesForm(bForm, b);
    signConcretesForm(cForm, c);

     signConcretesForm(aForm, d);
    signConcretesForm(bForm, e);
    signConcretesForm(cForm, f);
}

int main()
{
    std::cout << "--------------------EX 02---------------------" << std::endl << std::endl;

    std::cout << "--- Test execution successful ---" << std::endl << std::endl;
    executeConcretesForm();

    std::cout << std::endl << "--- Test execution form not signed --- " << std::endl << std::endl;
    executeConcretesFormFail();

    std::cout << std::endl << "--- Test execution form signed but grade not high enough to execute ---" << std::endl << std::endl;
    executeConcretesFormFailAgain();

    std::cout << std::endl << "--- Test signature ---" << std::endl << std::endl;
    testSignatures();

    return (0);
}

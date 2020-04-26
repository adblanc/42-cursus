/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:46:26 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 08:37:28 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

void    testUpperLimitCreation() {
    try {
        Bureaucrat  adrien("Adrien", 1);
        std::cout << adrien;

        std::cout << "Let's try to create a 0 grade bureaucrat" << std::endl;
        Bureaucrat("Adrien but too high", 0);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

void    testLowerLimitCreation() {
    try {
        Bureaucrat  adrien("Adrien", 150);
        std::cout << adrien;

        std::cout << "Let's try to create a 151 grade bureaucrat" << std::endl;
        Bureaucrat("Adrien but too lowkey", 151);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

void    testUpperLimitIncrement() {
    try {
        Bureaucrat  adrien("Adrien", 1);
        std::cout << adrien;

        std::cout << "Let's try to increment a 1 grade bureaucrat" << std::endl;
        adrien.incrementGrade();
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

void    testLowerLimitDecrement() {
    try {
        Bureaucrat  adrien("Adrien", 150);
        std::cout << adrien;

        std::cout << "Let's try to decrement a 150 grade bureaucrat" << std::endl;
        adrien.decrementGrade();
    } catch (const Bureaucrat::GradeTooLowException& e) {
        std::cout << e.what() << std::endl;
    }
}

void    testFormCreationLowerLimitSign() {
    try {
        Form form1("Form1", 1, 1);
        std::cout << form1 << std::endl;

        Form form2("Form2", 150, 150);
        std::cout << form2 << std::endl;

        std::cout << "Trying to create a 0 grade to sign form.." << std::endl;
        Form form3("Form3", 0, 1);
        std::cout << form3 << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    testFormCreationLowerLimitExec() {
    try {
        Form form1("Form1", 1, 1);
        std::cout << form1 << std::endl;

        Form form2("Form2", 150, 150);
        std::cout << form2 << std::endl;

        std::cout << "Trying to create a 0 grade to exec form.." << std::endl;
        Form form3("Form3", 1, 0);
        std::cout << form3 << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    testFormCreationUpperLimitExec() {
    try {
        Form form1("Form1", 1, 1);
        std::cout << form1 << std::endl;

        Form form2("Form2", 150, 150);
        std::cout << form2 << std::endl;

        std::cout << "Trying to create a 151 grade to exec form.." << std::endl;
        Form form3("Form3", 1, 151);
        std::cout << form3 << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    testFormCreationUpperLimitSign() {
    try {
        Form form1("Form1", 1, 1);
        std::cout << form1 << std::endl;

        Form form2("Form2", 150, 150);
        std::cout << form2 << std::endl;

        std::cout << "Trying to create a 151 grade to exec form.." << std::endl;
        Form form3("Form3", 151, 1);
        std::cout << form3 << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    testSignature() {
    try {
        Bureaucrat  adrien("Adrien", 150);
        Form        form("Form lvl 150", 150, 150);
        Form        form2("Form lvl 149", 149, 149);

        std::cout << adrien;

        std::cout << "Let's try to sign a 150 grade required form" << std::endl;
        adrien.signForm(form);

        std::cout << std::endl;

        std::cout << "Let's try to sign a 149 grade required form" << std::endl;
        adrien.signForm(form2);

        std::cout << std::endl << "Let's try to sign an already signed form" << std::endl;
        adrien.signForm(form);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    testLowerLimitCreation();
    std::cout << "------------------------------" << std::endl << std::endl;
    testUpperLimitCreation();
    std::cout << "------------------------------" << std::endl << std::endl;
    testLowerLimitDecrement();
    std::cout << "------------------------------" << std::endl << std::endl;
    testUpperLimitIncrement();

    std::cout << "--------------------PARTIE 2---------------------" << std::endl << std::endl;

    testFormCreationLowerLimitSign();
     std::cout << "------------------------------" << std::endl << std::endl;

     testFormCreationUpperLimitSign();
     std::cout << "------------------------------" << std::endl << std::endl;

    testFormCreationLowerLimitExec();
     std::cout << "------------------------------" << std::endl << std::endl;

    testFormCreationUpperLimitExec();
     std::cout << "------------------------------" << std::endl << std::endl;


    testSignature();
    return (0);
}

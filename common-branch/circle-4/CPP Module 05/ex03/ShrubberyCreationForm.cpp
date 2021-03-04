/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:20:04 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 09:06:43 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void):
Form("ShruberryCreationForm", 145, 137, "Default Target")
{

};

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target):
Form("ShruberryCreationForm", 145, 137, target)
{

};

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src):
Form(src.getName(), src.getGradeToSign(), src.getGradeToExec(), src.getTarget())
{
    *this = src;
};

ShrubberyCreationForm::~ShrubberyCreationForm()
{

};

ShrubberyCreationForm &ShrubberyCreationForm::operator= (const ShrubberyCreationForm &rhs)
{
    (void)rhs;
    return (*this);
};

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
    std::ofstream output;

    Form::execute(executor);
    output.open(this->getTarget() + "_shrubbery", std::ofstream::trunc);

    if (output.fail()) {
        std::cout << "Could not open the file : " + this->getTarget() + "_shrubbery" << std::endl;
        return ;
    }

    output << "   /\\   " << std::endl;
    output << "  /  \\  " << std::endl;
    output << " / o  \\ " << std::endl;
    output << "  ||||  " << std::endl;
    output.close();
}

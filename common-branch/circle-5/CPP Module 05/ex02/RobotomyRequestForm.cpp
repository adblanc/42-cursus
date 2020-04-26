/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:22:09 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 09:39:30 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void):
Form("RobotomyRequestForm", 72, 45, "Default target")
{
    srand(time(NULL));
};

RobotomyRequestForm::RobotomyRequestForm(std::string const &target):
Form("RobotomyRequestForm", 72, 45, target)
{
    srand(time(NULL));
};

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src):
Form(src.getName(), src.getGradeToSign(), src.getGradeToExec(), src.getTarget())
{
    *this = src;
};

RobotomyRequestForm::~RobotomyRequestForm()
{

};

RobotomyRequestForm &RobotomyRequestForm::operator= (const RobotomyRequestForm &rhs)
{
    (void)rhs;
    return (*this);
};

void RobotomyRequestForm::execute(Bureaucrat const & executor) const {
	std::string possibilities[] = {"success", "failure"};

    Form::execute(executor);
    std::cout << "*Psssssssssss psssssss*(bruits de perceuse), " + this->getTarget() + " robotomization " + possibilities[std::rand() % 2] << std::endl;
}

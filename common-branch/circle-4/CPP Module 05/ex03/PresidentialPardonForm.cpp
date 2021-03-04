/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:22:58 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 09:06:27 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void):
Form("PresidentialPardonForm", 25, 5, "Default Target")
{

};

PresidentialPardonForm::PresidentialPardonForm(std::string const &target):
Form("PresidentialPardonForm", 25, 5, target)
{

};

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &src):
Form(src.getName(), src.getGradeToSign(), src.getGradeToExec(), src.getTarget())
{
    *this = src;
};

PresidentialPardonForm::~PresidentialPardonForm()
{

};

PresidentialPardonForm &PresidentialPardonForm::operator= (const PresidentialPardonForm &rhs)
{
    (void)rhs;
    return (*this);
};

void PresidentialPardonForm::execute(Bureaucrat const & executor) const {
    Form::execute(executor);
    std::cout << this->getTarget() + " got forgiven by Safod Beeblebrox." << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:09:54 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 08:39:49 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat(void):
name("Bureaucrat lambda"), grade(1)
{

};

Bureaucrat::Bureaucrat(std::string const &name, int grade):
name(name), grade(grade)
{
    if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &src):
name(src.name), grade(src.grade)
{
    *this = src;
};

Bureaucrat::~Bureaucrat()
{

};

Bureaucrat &Bureaucrat::operator= (const Bureaucrat &rhs)
{
    (void)rhs;
    return (*this);
};

std::string Bureaucrat::getName(void) const {
    return this->name;
}

int Bureaucrat::getGrade(void) const {
    return this->grade;
}

void    Bureaucrat::incrementGrade(void) {
    if (this->grade - 1 < 1)
        throw Bureaucrat::GradeTooHighException();
    else
        this->grade--;
}

void    Bureaucrat::decrementGrade(void) {
    if (this->grade + 1 > 150)
        throw Bureaucrat::GradeTooLowException();
    else
        this->grade++;
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &b) {
    std::stringstream ss;

    ss << b.getGrade();
    out << b.getName() + ", bureaucrat grade " + ss.str() << std::endl;

    return out;
}

const char *Bureaucrat::GradeTooHighException::what(void) const throw() {
    return "Bureaucrat grade is too high.";
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw() {
    return "Bureaucrat grade is too low.";
}

Bureaucrat::GradeTooHighException::GradeTooHighException(void)
{

};

Bureaucrat::GradeTooHighException::GradeTooHighException(const Bureaucrat::GradeTooHighException &src)
{
    *this = src;
};

Bureaucrat::GradeTooHighException::~GradeTooHighException(void) throw()
{

};

Bureaucrat::GradeTooHighException &Bureaucrat::GradeTooHighException::operator= (const Bureaucrat::GradeTooHighException &rhs)
{
    (void)rhs;
    return (*this);
};

Bureaucrat::GradeTooLowException::GradeTooLowException(void)
{

};

Bureaucrat::GradeTooLowException::GradeTooLowException(const Bureaucrat::GradeTooLowException &src)
{
    *this = src;
};

Bureaucrat::GradeTooLowException::~GradeTooLowException(void) throw()
{

};

Bureaucrat::GradeTooLowException &Bureaucrat::GradeTooLowException::operator= (const Bureaucrat::GradeTooLowException &rhs)
{
    (void)rhs;
    return (*this);
};

void    Bureaucrat::signForm(Form &form) {
try {
    form.beSigned(*this);
    std::cout << this->getName() + " signs " + form.getName() << std::endl;
} catch (std::exception &e) {
    std::cout << this->getName() + " can't sign " + form.getName() + " because " + e.what() << std::endl;
}
}

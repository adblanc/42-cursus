/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:15:31 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 09:06:05 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(void):
name("Default form"), isSigned(false), gradeToSign(1), gradeToExec(1), target("Default target")
{

};

Form::Form(const Form &src):
name(src.name), isSigned(src.isSigned), gradeToSign(src.gradeToSign), gradeToExec(src.gradeToExec), target(src.target)
{
    *this = src;
};

Form::~Form()
{

};

Form &Form::operator= (const Form &rhs)
{
    (void)rhs;
    return (*this);
};

Form::Form(std::string const &name, int gradeToSign, int gradeToExec, std::string const &target):
name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExec(gradeToExec), target(target)
{
    if (gradeToSign > 150 || gradeToExec > 150)
        throw Form::GradeTooLowException();
    if (gradeToSign < 1 || gradeToExec < 1)
        throw Form::GradeTooHighException();
}

void    Form::beSigned(Bureaucrat const &b) {
    if (this->gradeToSign < b.getGrade())
        throw Form::GradeTooHighException();
    if (this->isSigned)
        throw Form::FormAlreadySigned();
    this->isSigned = true;
}

std::ostream &operator<<(std::ostream &out, Form const &f) {
    std::stringstream gradeToSign;
    std::stringstream gradeToExec;

    gradeToExec << f.getGradeToExec();
    gradeToSign << f.getGradeToSign();

    out << f.getName() + " form to sign : " + gradeToSign.str() +
     ", to exec : " + gradeToExec.str() << std::endl;

    return out;
}

void    Form::setTarget(std::string const &target) {
    this->target = target;
}

void    Form::execute(Bureaucrat const &executor) const {
    if (!this->isSigned)
        throw Form::FormNotSigned();
    if (executor.getGrade() > this->gradeToExec)
        throw Form::GradeTooHighException();
}

const char *Form::GradeTooHighException::what(void) const throw() {
    return "Form grade is too high.";
}

const char *Form::GradeTooLowException::what(void) const throw() {
    return "Form grade is too low.";
}

const char *Form::FormAlreadySigned::what(void) const throw() {
    return "Form is already signed";
}

const char *Form::FormNotSigned::what(void) const throw() {
    return "Form is not signed";
}

Form::GradeTooLowException::GradeTooLowException(void)
{

};

Form::GradeTooLowException::GradeTooLowException(const Form::GradeTooLowException &src)
{
    *this = src;
};

Form::GradeTooLowException::~GradeTooLowException() throw()
{

};

Form::GradeTooLowException &Form::GradeTooLowException::operator= (const Form::GradeTooLowException &rhs)
{
   (void)rhs;
    return (*this);
};

Form::GradeTooHighException::GradeTooHighException(void)
{

};

Form::GradeTooHighException::GradeTooHighException(const Form::GradeTooHighException &src)
{
    *this = src;
};

Form::GradeTooHighException::~GradeTooHighException() throw()
{

};

Form::GradeTooHighException &Form::GradeTooHighException::operator= (const Form::GradeTooHighException &rhs)
{
    (void)rhs;
    return (*this);
};

Form::FormAlreadySigned::FormAlreadySigned(void)
{

};

Form::FormAlreadySigned::FormAlreadySigned(const Form::FormAlreadySigned &src)
{
    *this = src;
};

Form::FormAlreadySigned::~FormAlreadySigned() throw()
{

};

Form::FormAlreadySigned &Form::FormAlreadySigned::operator= (const Form::FormAlreadySigned &rhs)
{
    (void)rhs;
    return (*this);
};

Form::FormNotSigned::FormNotSigned(void)
{

};

Form::FormNotSigned::FormNotSigned(const Form::FormNotSigned &src)
{
    *this = src;
};

Form::FormNotSigned::~FormNotSigned() throw()
{

};

Form::FormNotSigned &Form::FormNotSigned::operator= (const Form::FormNotSigned &rhs)
{
    (void)rhs;
    return (*this);
};


std::string Form::getName() const {
    return this->name;
}

int         Form:: getGradeToSign() const {
    return this->gradeToSign;
}

int         Form::getGradeToExec() const {
    return this->gradeToExec;
}

int         Form::getIsSigned() const {
    return this->isSigned;
}

std::string Form::getTarget() const {
    return this->target;
}


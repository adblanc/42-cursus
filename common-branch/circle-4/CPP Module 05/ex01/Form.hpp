/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:15:17 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 08:36:29 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

#include "Bureaucrat.hpp"


class Form
{
    public:
        Form(void);
        Form(std::string const &name, int gradeToSign, int gradeToExec);
        Form(const Form &src);
        ~Form();

        Form	&operator=(const Form &rhs);

         class GradeTooHighException: public std::exception
        {
            public:

                GradeTooHighException(void);
                GradeTooHighException(const GradeTooHighException &src);
                virtual ~GradeTooHighException() throw();

                virtual const char *what(void) const throw();

                GradeTooHighException	&operator=(const GradeTooHighException &rhs);
        };

        class GradeTooLowException: public std::exception
        {
            public:
            		GradeTooLowException(void);
                    GradeTooLowException(const GradeTooLowException &src);
                    virtual ~GradeTooLowException() throw();

                    virtual const char *what(void) const throw();

                    GradeTooLowException	&operator=(const GradeTooLowException &rhs);
        };

         class FormAlreadySigned: public std::exception
        {
            public:
            		FormAlreadySigned(void);
                    FormAlreadySigned(const FormAlreadySigned &src);
                    virtual ~FormAlreadySigned(void) throw();

                    virtual const char *what(void) const throw();

                    FormAlreadySigned	&operator=(const FormAlreadySigned &rhs);
        };

        std::string getName() const;
        int         getGradeToSign() const;
        int         getGradeToExec() const;
        int         getIsSigned() const;

        void        setIsIsSigned();

        void        beSigned(Bureaucrat const &);

    private:

    const std::string name;
    bool isSigned;
    const int gradeToSign;
    const int gradeToExec;

};

std::ostream &operator<<(std::ostream &, Form const &);

 #endif

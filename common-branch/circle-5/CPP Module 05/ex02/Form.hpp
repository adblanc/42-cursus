/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:15:17 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 08:46:53 by ablanc           ###   ########.fr       */
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
        Form(std::string const &name, int gradeToSign, int gradeToExec, std::string const &target);
        Form(const Form &src);
        virtual ~Form() = 0;


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
                    virtual ~FormAlreadySigned() throw();

                    virtual const char *what(void) const throw();

                    FormAlreadySigned	&operator=(const FormAlreadySigned &rhs);
        };

        class FormNotSigned: public std::exception
        {
            public:
            		FormNotSigned(void);
                    FormNotSigned(const FormNotSigned &src);
                    virtual ~FormNotSigned() throw();

                    virtual const char *what(void) const throw();

                    FormNotSigned	&operator=(const FormNotSigned &rhs);
        };

        void        setTarget(std::string const &);

        std::string getName() const;
        int         getGradeToSign() const;
        int         getGradeToExec() const;
        int         getIsSigned() const;
        std::string getTarget() const;

        void        setIsIsSigned();

        void        beSigned(Bureaucrat const &);

        virtual void    execute(Bureaucrat const & executor) const;

    private:
    Form	&operator=(const Form &rhs);

    const std::string name;
    bool isSigned;
    const int gradeToSign;
    const int gradeToExec;
    std::string target;

};

std::ostream &operator<<(std::ostream &, Form const &);

 #endif

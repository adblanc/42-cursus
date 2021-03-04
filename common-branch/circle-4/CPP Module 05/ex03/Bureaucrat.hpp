/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:03:42 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 09:01:17 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

class Form;

class Bureaucrat
{
    public:
        Bureaucrat(void);
        Bureaucrat(std::string const &name, int grade);
        Bureaucrat(const Bureaucrat &src);
        ~Bureaucrat();

        std::string getName() const;
        int         getGrade() const;

        void        incrementGrade();
        void        decrementGrade();

        void        signForm(Form &);
        void        executeForm(Form const & form);

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

    private:
        Bureaucrat	&operator=(const Bureaucrat &rhs);

        const std::string name;
        int grade;
};

std::ostream &operator<<(std::ostream &, Bureaucrat const &);


 #endif

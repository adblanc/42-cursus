/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:20:23 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 09:25:31 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include <string>
#include <iostream>
#include "Form.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"


class Intern
{
    private:

        typedef struct  s_forms
        {
            std::string const name;
            Form *(*new_form)(std::string const &target);
        }               t_forms;

    static const int form_nbr;

    static Form *createRobotomy(std::string const &target);
    static Form *createPresidential(std::string const &target);
    static Form *createShruberry(std::string const &target);

    static const t_forms forms[3];
    public:
        Intern(void);
        Intern(const Intern &src);
        ~Intern();

        Intern	&operator=(const Intern &rhs);

        Form *makeForm(std::string const &form, std::string const &target);

    private:

};


 #endif

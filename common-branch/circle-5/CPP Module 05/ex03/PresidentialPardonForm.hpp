/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:22:43 by adrien            #+#    #+#             */
/*   Updated: 2020/03/04 09:06:31 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "Form.hpp"

class PresidentialPardonForm: public Form
{
    public:
        PresidentialPardonForm(void);
        PresidentialPardonForm(std::string const &target);
        PresidentialPardonForm(const PresidentialPardonForm &src);
        ~PresidentialPardonForm();

        PresidentialPardonForm	&operator=(const PresidentialPardonForm &rhs);

        virtual void    execute(Bureaucrat const & executor) const;

    private:

};


 #endif

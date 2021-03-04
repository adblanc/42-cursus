/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 08:48:40 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 10:18:27 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_MATERIA_HPP
#define A_MATERIA_HPP

#include <string>
#include "ICharacter.hpp"

class ICharacter;

class AMateria
{
	private:
		AMateria(void);
		std::string _type;
		unsigned int _xp;

	public:

		AMateria(std::string const &type);
		AMateria(const AMateria &src);
        AMateria &operator=(const AMateria &rhs);
		virtual ~AMateria();

		std::string const & getType() const;
		unsigned int getXP() const;

		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);
};

#endif


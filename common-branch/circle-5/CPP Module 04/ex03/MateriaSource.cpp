/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:50:55 by ablanc            #+#    #+#             */
/*   Updated: 2020/03/03 10:23:35 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void)
{
	for (int i = 0; i < 4 ; i++)
		this->stock[i] = NULL;
};

void	MateriaSource::_deepCopy(const MateriaSource &s)
{
	for (int i = 0; i < 4 ; i++)
	{
		delete this->stock[i];
		if (s.stock[i])
			this->stock[i] = s.stock[i]->clone();
		else
			this->stock[i] = NULL;
	}
};

MateriaSource::MateriaSource(const MateriaSource &src)
{
	this->_deepCopy(src);
};

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4 ; i++)
		delete this->stock[i];
};

MateriaSource &MateriaSource::operator= (const MateriaSource &rhs)
{
    if (this != &rhs)
		this->_deepCopy(rhs);
    return (*this);
};

void	MateriaSource::learnMateria(AMateria *m)
{
	int i;

	i = 0;
	while(i < 4 && this->stock[i])
		i++;
	if (i == 4)
		return ;

	this->stock[i] = m;
};

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4 ; i++)
	{
		if (this->stock[i] && this->stock[i]->getType() == type)
			return this->stock[i]->clone();
	}
	return NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:24:02 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 15:30:45 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pony.hpp"

void	Pony::setAge(int value)
{
	age = value;
}

void	Pony::setSpeed(float value)
{
	speed = value;
}

void	Pony::bringToLife()
{
	alive = true;
}

void	Pony::kill()
{
	alive = false;
}


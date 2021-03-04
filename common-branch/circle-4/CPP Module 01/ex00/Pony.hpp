/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:24:12 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 15:37:24 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONY_H
# define PONY_H

class Pony
{
	public:

	void	setAge(int value);
	void	setSpeed(float value);
	void	bringToLife();
	void	kill();

	private:
	int		age;
	float	speed;
	bool	alive;
};

#endif

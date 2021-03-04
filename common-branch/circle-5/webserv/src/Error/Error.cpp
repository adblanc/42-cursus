/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:45:05 by adrien            #+#    #+#             */
/*   Updated: 2020/10/07 19:08:50 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

Error::Error(const std::string &statusCode, const std::string &description, bool eoc) : statusCode(statusCode), description(description), endOfConnection(eoc)
{
};

Error::Error(void) :
	statusCode(), description(), endOfConnection(false)
{

};

Error::~Error()
{
}

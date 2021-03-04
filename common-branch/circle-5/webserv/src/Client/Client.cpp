/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:39:33 by adrien            #+#    #+#             */
/*   Updated: 2020/10/19 16:44:08 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(const std::string &ip, size_t &port, int socket):
ip(ip), port(port), socket(socket)
{
}

Client::Client(void)
{
}

Client::Client(const Client &src)
{
    *this = src;
}

Client::~Client()
{
}

Client &Client::operator=(const Client &rhs)
{
    if (this != &rhs)
    {
		this->ip = rhs.ip;
		this->port = rhs.port;
        this->socket = rhs.socket;
    }

    return (*this);
}

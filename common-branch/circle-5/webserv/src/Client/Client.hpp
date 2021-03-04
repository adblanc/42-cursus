/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:39:25 by adrien            #+#    #+#             */
/*   Updated: 2020/10/06 11:44:01 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "../headers.hpp"

struct Client
{
        Client(const std::string &ip, size_t &port, int socket);
        Client(void);
        Client(const Client &src);
        ~Client();
        Client	&operator=(const Client &rhs);

		std::string ip;
		size_t		port;
        int         socket;
};


 #endif

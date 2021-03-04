/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:45:16 by adrien            #+#    #+#             */
/*   Updated: 2020/10/07 19:07:41 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# include <string>

struct Error
{
	Error(const std::string &statusCode, const std::string &description = "", bool eoc = false);
	Error(void);
	~Error();

	std::string statusCode;
	std::string	description;
	bool		endOfConnection;
};




 #endif

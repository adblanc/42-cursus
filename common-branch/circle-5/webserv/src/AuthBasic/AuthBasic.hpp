/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AuthBasic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:30:45 by adrien            #+#    #+#             */
/*   Updated: 2020/10/19 17:18:24 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTHBASIC_HPP
# define AUTHBASIC_HPP

# include "../headers.hpp"
# include "../utils.hpp"

class AuthBasic
{
    public:

        struct User {
            User(const std::string &id, const std::string &password):
            id(id), password(password)
            {}
            std::string id;
            std::string password;
        };

        AuthBasic(void);
        AuthBasic(const AuthBasic &src);
        ~AuthBasic();

        AuthBasic	&operator=(const AuthBasic &rhs);

        bool    isActive(void);
        void    turnOff(void);

        std::vector<User>    ids;
        std::string                 realm;

        static std::string     base64Encode(unsigned char const* bytes_to_encode, unsigned int in_len);
        static std::string     base64Decode(std::string const &encoded_string);



    private:

    static const std::string base64Chars;

    bool            isOff;
};


 #endif

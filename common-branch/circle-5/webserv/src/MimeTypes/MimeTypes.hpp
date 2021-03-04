/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeTypes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:05:28 by adrien            #+#    #+#             */
/*   Updated: 2020/09/23 14:36:49 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIMETYPES_HPP
# define MIMETYPES_HPP

# include "../headers.hpp"
# include "../utils.hpp"

class MimeTypes
{
    public:
        MimeTypes(void);
        MimeTypes(const MimeTypes &src);
        ~MimeTypes();

        MimeTypes	&operator=(const MimeTypes &rhs);
        
        std::string		getMimeType(const std::string &filePath);
		std::string		getRevMimeType(const std::string &contType);

    private:

    static std::map<std::string, std::string> createMIMETypes(void);
    static const std::map<std::string, std::string>			_data;

};

#endif

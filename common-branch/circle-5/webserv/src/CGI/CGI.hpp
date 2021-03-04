/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 19:34:18 by adrien            #+#    #+#             */
/*   Updated: 2020/10/22 17:20:49 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "../headers.hpp"
# include "../utils.hpp"
# include "../ConfigParser/ConfigParser.hpp"
# include "../Request/Request.hpp"
# include "../Error/Error.hpp"

struct Client;

class CGI
{
    enum STATE
    {
        SHOULD_PARSE_HEADERS,
        IS_SENDING_HEADERS,
        IS_SENDING_BODY
    };

    public:
        CGI(Request *rqh, const Client *client);
        ~CGI();

        static std::list<std::string>       forbiddenHttpHeaders;

        void								process(const std::string &executablePath, const std::string &uriRooted);
        bool								send(const std::string &statusLine);

        bool                                isProcessed(void);

        bool                                clean(bool ret = true);

    private:


		Request						        *_rqh;
		const Client						*_client;

        void                                _verifyCgiHeaders(void);
        void                                _prepareHeaders(const std::string &statusLine);

        char **                             _getArgs(const std::string &executablePath, const std::string &uriRooted);
        char **                             _getEnv(const std::string &uriRooted);
        void                                _addReqHeadersToEnv(std::list<std::string> &env);
        std::string		                    _formatHttpHeader(const std::string &name, const std::string &value);
        bool                                _isHeaderToSkip(const std::string &key);

        void								_handleResult();
        void                                _writeBodyToPipeIn(const std::string &uriRooted);

        bool                                _writeToClientUntilEnd(void);

        void                                _freeArgsAndEnv(void);

		char **                             _args;
		char **                             _env;
		std::string							_bodyBuff;
		std::string							_headersBuff;
        int                                 _tmpFd;
        std::string                         _tmpName;


        STATE                               _state;

        std::string                         _buffer;
        bool                                _processed;
        ssize_t                             _contentLen;
        ssize_t                             _contentSent;

        int cgiPipe[2];
};

# include "../Client/Client.hpp"

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:10:27 by fcadet            #+#    #+#             */
/*   Updated: 2020/10/19 16:45:33 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "../headers.hpp"
# include "../ConfigParser/ConfigParser.hpp"
# include "../Client/Client.hpp"
# include "../Error/Error.hpp"

class Request
{
	public:


	struct			reqLine_t
	{
		std::string	method;
		std::string uri;
		std::string queryString;
		std::string version;
	};

	struct			complete_t
	{
		complete_t(void) : method(false), uri(false), version(false), headers(false), body(false), all(false) {}

		bool		method;
		bool		uri;
		bool		version;
		bool		headers;
		bool		body;
		bool		all;
	};

	struct			body_t
	{
		body_t(void) : tmp_name(""), tmp_fd(-1), cont_len(-1), tmp_len(0), read_chunk_sz(true), chunk_sz(0) {}

		std::string						tmp_name;
		int								tmp_fd;
		ssize_t							cont_len;
		ssize_t							tmp_len;
		bool							read_chunk_sz;
		ssize_t							chunk_sz;
	};

	Request(void);
	~Request();

	template <typename T>
		struct HandlerReturn
		{
			T		value;
			bool	success;

			HandlerReturn(bool suc = true) : value(), success(suc) {}
			HandlerReturn(const T &value, bool suc = true) : value(value), success(suc) {}
		};

		struct Accept
		{
			std::string	type;
			float		quality;
		};

		struct Host
		{
			std::string	uri;
			size_t		port;
		};

		struct Authorization
		{
			std::string type;
			std::string credentials;
		};

		typedef std::vector<utils::pair<std::string, std::string> >	keyValueVec;

		typedef HandlerReturn<std::string>							methodReturn;
		typedef HandlerReturn<std::string>							uriReturn;
		typedef HandlerReturn<std::string>							versionReturn;

		typedef HandlerReturn<Host>									hostReturn;
		typedef HandlerReturn<Authorization>						authReturn;
		typedef HandlerReturn<std::vector<Accept> > 				acceptReturn;
		typedef HandlerReturn<std::string>							userAgentReturn;
		typedef HandlerReturn<std::string>							refererReturn;
		typedef HandlerReturn<std::string>							contentTypeReturn;
		typedef HandlerReturn<std::string>							contentLengthReturn;
		typedef HandlerReturn<keyValueVec>							queryStringReturn;

		typedef HandlerReturn<body_t>						bodyReturn;

		methodReturn								getMethod() const;
		uriReturn									getUri() const;
		versionReturn								getVersion() const;

		hostReturn									getHost() const;
		authReturn									getAuthorization() const;
		acceptReturn								getAcceptLanguage() const;
		acceptReturn								getAcceptCharset() const;
		userAgentReturn								getUserAgent() const;
		refererReturn								getReferer() const;
		contentLengthReturn							getContentLength() const;
		contentTypeReturn							getContentType() const;
		queryStringReturn							getQueryString() const;

		std::string									getRawQueryString() const;
		std::string									getRawHeaders(void) const;
		const	std::map<std::string, std::string> 	&getHeaders(void);


		ConfigParser::ServerInfos					*getSrvInf();
		ConfigParser::LocationInfos					*getLoc();

		ssize_t										readBody(char *buff, size_t buff_size);
		ssize_t										getTmpFd(void);
		void										setTmpFd(ssize_t fd);

		bool										isComplete(void) const;
		bool										isError(void) const;

		void										setSrvInf(const ConfigParser::ServerInfos &srvInf);

		Error								error;

		std::string							str_buff;
		reqLine_t							reqLine;
		std::map<std::string, std::string>	headers;
		body_t								body;
		struct timeval						age;
		complete_t							complete;
		bool								maxSzTested;
		ConfigParser::ServerInfos			srvInf;
		ConfigParser::LocationInfos			locInf;
		std::string							host;
		int									port;

		bool								isDefaultSrvInf;
		const Client						*client;

	private:

		acceptReturn								_parseAcceptHeader(const std::string &) const;
		float										_getQuality(std::vector<std::string> &charset) const;
		keyValueVec									_parseKeyValues(const std::vector<std::string> &keyValues)  const;

		HandlerReturn<std::string>					_getStringHeaderValue(const std::string &name) const;

};

#endif

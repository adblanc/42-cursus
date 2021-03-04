/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 11:36:03 by adrien            #+#    #+#             */
/*   Updated: 2020/10/22 17:43:24 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "../headers.hpp"
# include "../utils.hpp"
# include "../MimeTypes/MimeTypes.hpp"
# include "../CGI/CGI.hpp"
# include "../Client/Client.hpp"
# include "../Error/Error.hpp"

class	Server;
class	ConfigParser;

class Response
{
    public:
		typedef		void (Response::*treatment)(void);
        Response(Request *req, Server *srv);
        ~Response();

		bool							send(bool withBody = true);
		bool							isError(void);
		std::string						getStatusCode(void);

		struct		rspBody
		{
			rspBody(void) : none(false), str(""), fromFile(false), path(), fileLen(0), fileFd(-1) {}
			~rspBody()
			{
				if (fileFd != -1)
					close(fileFd);
			}

			bool			none;
			std::string		str;
			bool			fromFile;
			std::string		path;
			ssize_t			fileLen;
			int				fileFd;
		};

		void							setError(const std::string &errorCode);

    private:
		static std::map<std::string, std::string>			createStatusesMap(void);
		static std::map<std::string, Response::treatment>	createTreatmentsMap(void);

        void        setHeader(const std::string &name, const std::string &value);
        void        setBody(const std::string &body);
		void		setLastMod(time_t t);

		const std::string				getErrorPagePath(const std::string &errorCode);
		bool							getIndex(struct stat &file_stat);
		std::string						getFileType(std::string &full_uri);
		std::string						getFileName(std::string &full_uri);

		bool							isAuthenticated(void);
		bool							createAutoIndex(void);
		void							addFileToDirectoryListing(const std::string &name, const std::string &href, bool isDir);
		std::string						getPathBefore(const std::string &path);
		const std::string				getStatusMessage(const std::string &statusCode);
		void							setDefaultErrorPage(const std::string &errorCode, const std::string &statusMsg);
		bool							_isReqForCgi(void);

		void							_setContentLength(void);

		void							_setAllowHeader(void);


		void							putPost(int flag);

		void							get(void);
		void							head(void);
		void							post(void);
		void							put(void);
		void							del(void);
		void							connect(void);
		void							options(void);
		void							trace(void);

		static const std::map<std::string, std::string>			_statuses;
		static const std::string								_defaultErrorPage;
		static const std::map<std::string, treatment>			_treatments;
		static MimeTypes										_mimeTypes;

		std::string												_statusLine;
		std::map<std::string, std::string>						_headerFields;
		rspBody													_body;

		Request													*_req;
		Server													*_srv;
		const Client											*_client;
		std::string												_uriRooted;
		CGI														_cgi;
		bool													_error;
		bool													_defaultError;

		std::string												_cgiExecutablePath;

        STATE                             						_state;
		std::string												_headers;
        ssize_t													_contentSent;

		struct _cgiExtensionMatch
		{
			_cgiExtensionMatch(const std::string& extension) : extension(extension) {}

			bool operator()(const ConfigParser::Cgi &cgi)
			{
				return cgi.extension == extension;
			}

			std::string extension;
		};
};

# include "../Server/Server.hpp"
# include "../ConfigParser/ConfigParser.hpp"

 #endif

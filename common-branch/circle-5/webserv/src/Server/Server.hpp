/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:23:04 by fcadet            #+#    #+#             */
/*   Updated: 2020/10/19 16:52:18 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "../headers.hpp"
# include "../ConfigParser/ConfigParser.hpp"
# include "../RequestMap/RequestMap.hpp"
# include "../Client/Client.hpp"

class Server
{

	public:
		struct	Socket
		{
			size_t	port;
			int 	fd;
		};

		struct	Proxy
		{
			int				fd;
			std::string		buff;
		};

		typedef struct Socket Socket;

		Server(const ConfigParser::serverConfigs &servers, unsigned int sleepTime = SLEEP_TIME);
		~Server();

		void						run(void);
		void						addNewProxy(int fd, std::string ip, std::string port);
		ConfigParser::ServerInfos	getRoutedServer(int fd, const std::string &hostName) const;

	private:
		void						_cleanTmpDir(bool cleanRunning = true);
		ConfigParser::ServerInfos	_getDefaultServer(size_t port);
		bool						_sendError(const Error &error, int fd, bool withBody = true);
		void						_cleanFd(int fd, bool all = false, bool cli = false);
		void						_delProxy(int fd);
		void						_proxyCom(void);

		void						_displayReq(int fd);

		std::vector<Socket>					_serverSockets;

		struct sockaddr_in					_servAddr;
		fd_set								_readSet;
		fd_set								_setSrc;
		fd_set								_writeSet;
		unsigned int						_sleepTime;
		RequestMap							_reqMap;

		std::map<int, Proxy>				_proxyMap;
};

#endif

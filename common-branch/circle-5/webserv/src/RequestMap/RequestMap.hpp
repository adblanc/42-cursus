/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestMap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 14:08:49 by adrien            #+#    #+#             */
/*   Updated: 2020/10/19 18:05:35 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_MAP_HPP
# define REQUEST_MAP_HPP

# include "../headers.hpp"
# include "../Request/Request.hpp"
# include "../Error/Error.hpp"
# include "../ConfigParser/ConfigParser.hpp"

class Response;
class Server;

struct Client;

class RequestMap
{
	public:
		RequestMap(const ConfigParser::serverConfigs &servers);
		~RequestMap();

		void	parseReqFrom(int fd);
		Request	&getRequest(int fd);
		void	delReq(int fd);
		void	getTimedOut(std::vector<int> &timedOut);

		Response	&getResponse(int fd, Server *srv);
		void		delRsp(int fd);
		
		ConfigParser::ServerInfos	getRoutedServer(const int &fd, bool wantDefaultServ = false);

		void	addClient(const std::string &ip, size_t &port, int &socket);
		Client	&getClient(int fd);
		void	eraseClient(int fd);
		const std::map<int, Client>	&clients(void);

	private:
		bool	_getMethod(Request &req);
		bool	_getUri(Request &req);
		bool	_getVersion(Request &req);
		bool	_getHeaders(Request &req);
		bool	_getBody(const int &fd);
		bool	_treatChunked(Request &req, std::map<std::string, std::string>::const_iterator it);
		bool	_treatLength(Request &req);
		void	_getServer(const int &fd);
		void	_getLocation(Request &req);
		void	_verifyMethod(Request &req);

		void	_setQueryString(Request &req);	


		std::map<int, Request>				_map;
		const ConfigParser::serverConfigs	&_servers;	
		std::map<int, Response>				_rsp;		
		std::map<int, Client>				_clients;
};

# include "../Client/Client.hpp"
# include "../Response/Response.hpp"
# include "../Server/Server.hpp"

#endif

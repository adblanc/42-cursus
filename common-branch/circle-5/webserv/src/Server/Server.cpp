/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:18:44 by fcadet            #+#    #+#             */
/*   Updated: 2020/10/22 18:47:32 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const ConfigParser::serverConfigs &servers, unsigned int sleepTime):
_sleepTime(sleepTime * 1000), _reqMap(servers)
{
	int reuse = 1;

	_cleanTmpDir(false);

	FD_ZERO(&_readSet);
	FD_ZERO(&_setSrc);
	FD_ZERO(&_writeSet);

	for (ConfigParser::serverConfigs::const_iterator it = servers.begin(); it != servers.end(); it++)
	{
		for (ConfigParser::VecAddress::const_iterator et = it->addresses.begin(); et != it->addresses.end(); et++)
		{

			Socket newSocket;

			newSocket.port = et->port;

			if ((newSocket.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
				utils::exitWithError("socket()");

			fcntl(newSocket.fd, F_SETFL, O_NONBLOCK);
			utils::memset(&_servAddr, 0, sizeof(_servAddr));
			if (utils::initSockAddr(&_servAddr, et->host, et->port))
				utils::exitWithError("initSockAddr()");

			if (setsockopt(newSocket.fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0)
				utils::perror("setsockopt (SO_REUSEPORT) failed");

			if (bind(newSocket.fd, (struct sockaddr *)&_servAddr, sizeof(_servAddr)) < 0)
				utils::exitWithError("bind()");
			if (listen(newSocket.fd, MAX_HOST_NB) < 0)
				utils::perror("listen()");

			_serverSockets.push_back(newSocket);
			FD_SET(newSocket.fd, &_setSrc);
		}
	}
}

void Server::_cleanTmpDir(bool cleanRunning)
{
	DIR *dir = opendir("./tmp");
	struct dirent *tmp;
	std::string concat;

	if (!dir)
		utils::exitWithError("No /tmp directory\n");
	while ((tmp = readdir(dir)))
	{
		if (tmp->d_name[0] != '.' || (cleanRunning && !utils::strCmp(tmp->d_name, ".running")))
		{
			concat = "./tmp/";
			concat += tmp->d_name;
			unlink(concat.c_str());
		}
	}
	closedir(dir);
}

Server::~Server()
{
	for (std::map<int, Client>::const_iterator cli_it = _reqMap.clients().begin(); cli_it != _reqMap.clients().end(); ++cli_it)
		close(cli_it->first);
	for (std::map<int, Proxy>::iterator prox_it = _proxyMap.begin(); prox_it != _proxyMap.end(); ++prox_it)
		close(prox_it->first);

	_cleanTmpDir();
}

void	Server::_displayReq(int fd)
{
	Request &req = _reqMap.getRequest(fd);
	Response &rsp = _reqMap.getResponse(fd, this);

	std::string statusCode = rsp.getStatusCode();

	statusCode += statusCode.size() ? "" : "200";

	if (std::string(ENV) == "development")
		std::cout << CYAN
		<< req.getMethod().value + " " + YELLOW + req.getUri().value
		<< ((statusCode < "300") ? GREEN : RED)
		<< " " << statusCode << " "
		<< BLUE << "(fd: " << fd << ")" << COLOR_END << std::endl;
}

void Server::run(void)
{
	int selectRet;
	int newSocket;
	struct timeval timeOut = utils::msToTimeval(0);

	while (true)
	{
		_readSet = _setSrc;
		_writeSet = _setSrc;
		if ((selectRet = select(FD_SETSIZE, &_readSet, &_writeSet, NULL, &timeOut)) == -1)
			utils::exitWithError("select()");
		else if (selectRet > 0)
		{
			std::vector<int> timedOut;

			_reqMap.getTimedOut(timedOut);
			for (std::vector<int>::iterator it = timedOut.begin(); it != timedOut.end(); ++it)
				_reqMap.getRequest(*it).error = Error("408", "timeout", true);

			for (std::vector<Socket>::iterator it = _serverSockets.begin(); it != _serverSockets.end(); it++)
			{
				if (FD_ISSET(it->fd, &_readSet))
				{
					struct sockaddr_in clientAddr;
					size_t addrLength = sizeof(clientAddr);

					if ((newSocket = accept(it->fd, (struct sockaddr *)&clientAddr,
											(socklen_t *)&addrLength)) < 0)
						utils::exitWithError("accept()");
					std::cout << WHITE << "New connection " << BLUE << "(fd: " << newSocket << ")" << COLOR_END << std::endl;

					_reqMap.addClient(utils::ft_inet_ntoa(clientAddr.sin_addr), it->port, newSocket);
					fcntl(newSocket, F_SETFL, O_NONBLOCK);
					FD_SET(newSocket, &_setSrc);
				}
			}
			_proxyCom();
			for (std::map<int, Client>::const_iterator it = _reqMap.clients().begin(); it != _reqMap.clients().end();)
			{
				std::map<int, Client>::const_iterator next_it = it;
				++next_it;
				int fd = it->first;
				Request &req = _reqMap.getRequest(fd);
				bool isConnect = req.getMethod().value == "CONNECT";

				try
				{
					bool shouldRead = !(req.isError() || req.isComplete());

					if (FD_ISSET(fd, &_writeSet))
					{
						if (req.isError())
						{
							try
							{
								shouldRead = false;
								_sendError(req.error, fd, req.getMethod().value != "HEAD");
							}
							catch (const Error &error)
							{
								_cleanFd(fd, true);
								std::cout << WHITE << "Client disconnected " << BLUE << "(fd: " << fd << ", remaining: " << _reqMap.clients().size() << ")"
									<< COLOR_END << std::endl;
							}
						}
						else if (req.isComplete())
						{
							shouldRead = false;
							Response &rsp = _reqMap.getResponse(fd, this);
							if (rsp.send())
							{
								_displayReq(fd);
								_cleanFd(fd, false, !rsp.isError() && isConnect);
							}
						}
					}
					if (shouldRead && FD_ISSET(fd, &_readSet))
						_reqMap.parseReqFrom(fd);
					it = next_it;
				}
				catch (const Error &error)
				{
					if (error.statusCode == "client disconnected")
					{
						_cleanFd(fd, true);
						std::cout << WHITE << "Client disconnected " << BLUE << "(fd: " << fd << ", remaining: " << _reqMap.clients().size() << ")"
							<< COLOR_END << std::endl;
						it = next_it;
						continue ;
					}
					if (!req.isError())
						req.error = error;
				}
			}
		}
		usleep(_sleepTime);
	}
}

bool Server::_sendError(const Error &error, int fd, bool withBody)
{
	Request		&req = _reqMap.getRequest(fd);
	if (error.statusCode == "client disconnected")
	{
		_cleanFd(fd, true);
		return true;
	}
	else
	{
		if (!req.isDefaultSrvInf)
			req.setSrvInf(_reqMap.getRoutedServer(fd, true));

		Response &rsp = _reqMap.getResponse(fd, this);
		if (rsp.send(withBody))
		{
			 bool endOfConnection = error.endOfConnection;
			_displayReq(fd);
			_cleanFd(fd, endOfConnection);
			return endOfConnection;
		}
	}
	return false;
}


void Server::_cleanFd(int fd, bool all, bool cli)
{
	_reqMap.delReq(fd);
	_reqMap.delRsp(fd);
	if (all)
	{
		close(fd);
		FD_CLR(fd, &_setSrc);
	}
	if (all || cli)
		_reqMap.eraseClient(fd);
}

void		Server::_delProxy(int fd)
{
	close(_proxyMap[fd].fd);
	close(fd);
	FD_CLR(_proxyMap[fd].fd, &_setSrc);
	FD_CLR(fd, &_setSrc);
	_proxyMap.erase(_proxyMap[fd].fd);
	_proxyMap.erase(fd);
	std::cout << WHITE << "Client disconnected " << BLUE << "(fd: " << fd << ", remaining: " << _reqMap.clients().size() << ")"
		<< COLOR_END << std::endl;
}

void		Server::addNewProxy(int fd, std::string ip, std::string port)
{
    int										targSocket;
	struct sockaddr_in						targAddr;

    if ((targSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		throw Error("500", "add new proxy socket");
	if (utils::initSockAddr(&targAddr, ip, port))
		throw Error("400", "add new proxy init sock addr");
	if (connect(targSocket, (struct sockaddr *)&targAddr, sizeof(targAddr)) < 0)
		throw Error("500", "add new proxy connect");
	fcntl(targSocket, F_SETFL, O_NONBLOCK);
	_proxyMap[fd].fd = targSocket;
	_proxyMap[targSocket].fd = fd;
	FD_SET(targSocket, &_setSrc);
	std::cout << WHITE << "Connection to proxy " << BLUE << "(fd: " << fd << ")" << COLOR_END << std::endl;
}

void		Server::_proxyCom(void)
{
	std::map<int, Proxy>::iterator		prox;

	if (!PROXY_ACTIVE)
		return ;

    char				buffer[BUFFER_SIZE];
	ssize_t				readRet;
	ssize_t				writeRet;

	for (std::map<int, Proxy>::iterator prox = _proxyMap.begin(); prox != _proxyMap.end(); ++prox)
	{
		if (_reqMap.clients().find(prox->first) != _reqMap.clients().end())
			continue ;
		if (FD_ISSET(prox->second.fd, &_writeSet))
		{
			if (prox->second.buff.empty())
			{
				if (!FD_ISSET(prox->first, &_readSet))
					continue ;
				if ((readRet = read(prox->first, buffer, BUFFER_SIZE)) <= 0)
				{
					_delProxy(prox->first);
					continue ;
				}
				buffer[readRet] = '\0';
				prox->second.buff.append(buffer, readRet);
			}
			if ((writeRet = write(prox->second.fd, prox->second.buff.c_str(), prox->second.buff.size())) <= 0)
			{
				_delProxy(prox->first);
				continue ;
			}
			prox->second.buff = prox->second.buff.substr(writeRet);
		}
	}
}

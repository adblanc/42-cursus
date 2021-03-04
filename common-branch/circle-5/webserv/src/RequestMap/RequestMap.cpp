/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestMap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:34:58 by adrien            #+#    #+#             */
/*   Updated: 2020/10/22 18:47:37 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestMap.hpp"

RequestMap::RequestMap(const ConfigParser::serverConfigs &servers) : _map(), _servers(servers)
{
}

RequestMap::~RequestMap()
{
}

Request	&RequestMap::getRequest(int fd)
{
	return _map[fd];
}

Response	&RequestMap::getResponse(int fd, Server *srv)
{
	std::map<int, Response>::iterator it = _rsp.find(fd);

	if (it != _rsp.end())
		return it->second;

	return _rsp.insert(std::pair<int, Response>(fd, Response(&_map[fd], srv))).first->second;
}

void		RequestMap::delRsp(int fd)
{
	_rsp.erase(fd);
}

void	RequestMap::addClient(const std::string &ip, size_t &port, int &socket)
{
	_clients[socket] = Client(ip, port, socket);
}

Client	&RequestMap::getClient(int fd)
{
	return _clients[fd];
}

void	RequestMap::eraseClient(int fd)
{
	_clients.erase(fd);
}

const std::map<int, Client>	&RequestMap::clients(void)
{
	return _clients;
}

void	RequestMap::parseReqFrom(int fd)
{
	try
	{
		Request		&req = _map[fd];

		if (!req.client)
			req.client = &_clients[fd];

		char		buffer[BUFFER_SIZE + 1] = {0};
		ssize_t		read_size = 0;

		if ((read_size = read(fd, buffer, BUFFER_SIZE)) <= 0)
			throw Error("client disconnected");

		buffer[read_size] = '\0';
		req.str_buff.append(buffer, read_size);

		if (utils::isTelnetEnd(req.str_buff))
			throw Error("client disconnected");

		if (!req.complete.method)
			if (_getMethod(req))
				return ;
		if (req.complete.method && !req.complete.uri)
			if (_getUri(req))
				return ;
		if (req.complete.uri && !req.complete.version)
			if (_getVersion(req))
				return ;
		if (req.complete.version && !req.complete.headers)
			if (_getHeaders(req))
				return ;
		if (req.complete.headers && !req.complete.body)
			if (_getBody(fd))
				return ;
		if (req.complete.body && !req.complete.all)
		{
			req.complete.all = true;
			_verifyMethod(req);
		}
	}
	catch (const Error &error)
	{
		throw (Error(error.statusCode, error.description, true));
	}
}

void		RequestMap::getTimedOut(std::vector<int> &timedOut)
{
	struct timeval		time;

	timedOut.clear();
	gettimeofday(&time, NULL);
	for (std::map<int, Request>::iterator req = _map.begin(); req != _map.end(); ++req)
	{
		if (req->second.client && !req->second.complete.all && utils::timeValToMs(time) - utils::timeValToMs(req->second.age) > REQ_TIMEOUT)
			timedOut.push_back(req->first);
	}
}

void		RequestMap::_getServer(const int &fd)
{
	Request			&req = _map[fd];

	std::map<std::string, std::string>::iterator		host;
    std::vector<std::string>							uriAndPort;

	if ((host = req.headers.find("host")) == req.headers.end())
		throw Error("400", "No host header");
    utils::split(uriAndPort, host->second, ":", utils::ONESPLIT);
    req.host = !uriAndPort.size() ? "" : uriAndPort[0];
	req.port = uriAndPort.size() < 2 ? 80 : utils::stoi(uriAndPort[1].c_str());
	req.srvInf = getRoutedServer(fd);
}

ConfigParser::ServerInfos		RequestMap::getRoutedServer(const int &fd, bool wantDefaultServ)
{
	ConfigParser::ServerInfos 	defaultServer;
	bool						defaultFound = false;
	size_t						port = _clients[fd].port;
	Request						&req = _map[fd];

	for (ConfigParser::serverConfigs::const_iterator it = _servers.begin(); it != _servers.end(); it++)
	{
		for (ConfigParser::VecAddress::const_iterator et = it->addresses.begin() ; et != it->addresses.end() ; et++)
		{
			if (et->port == port)
			{
				if (!defaultFound)
				{
					if (wantDefaultServ)
					{
						req.isDefaultSrvInf = true;
						return *it;
					}
					defaultServer = *it;
					defaultFound = true;
				}
				for (std::vector<std::string>::const_iterator st = it->serverNames.begin() ; st != it->serverNames.end() ; st++)
					if (*st == req.host)
						return *it;
			}
		}
	}

	req.isDefaultSrvInf = true;
	return defaultServer;
}

void		RequestMap::_getLocation(Request &req)
{
	for (std::vector<ConfigParser::LocationInfos>::iterator it = req.srvInf.locations.begin(); it != req.srvInf.locations.end(); ++it)
	{
		if (!req.reqLine.uri.find(it->uri))
		{
			req.locInf = *it;
			return ;
		}
	}
	if (req.reqLine.method != "CONNECT")
		throw Error("403");
}

void	RequestMap::_verifyMethod(Request &req)
{
	if (req.reqLine.method == "CONNECT" && (!req.srvInf.connect || !PROXY_ACTIVE))
		throw Error("405", "verify method connect");

	if (!req.locInf.methods.size())
		return ;
	for (std::vector<std::string>::iterator it = req.locInf.methods.begin(); it != req.locInf.methods.end(); ++it)
		if (req.reqLine.method == *it)
			return ;

	throw Error("405", "verify method");
}

bool		RequestMap::_treatChunked(Request &req, std::map<std::string, std::string>::const_iterator it)
{
	size_t			found;

	if (req.body.cont_len < 0)
	{
		if (it->second != "chunked")
			throw Error("501");
		req.body.cont_len = 0;
		req.body.tmp_name = "tmp/" + utils::generateTmpName();
		if ((req.body.tmp_fd = open(req.body.tmp_name.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666)) < 0)
			throw Error("500");
	}

	while ((found = req.str_buff.find("\r\n")) != std::string::npos)
	{
		if (req.body.read_chunk_sz)
		{
			if (found == std::string::npos)
				return (true);
			if ((req.body.chunk_sz = utils::stringToSizeT(utils::toLowerCase(req.str_buff.substr(0, found)), true)) < 0)
				throw Error("400");
			req.body.read_chunk_sz = false;
			if ((size_t)(req.body.tmp_len += req.body.chunk_sz) > req.locInf.clientMaxBodySizeInBytes)
				throw Error("413", "client max body size in chunked");
			req.str_buff = req.str_buff.substr(found + 2);

			if (!req.body.chunk_sz)
			{
				req.complete.body = true;
				break;
			}
		}
		else
		{
			if (req.str_buff.size() < (size_t)req.body.chunk_sz + 2)
				return (true);
			if (!req.body.chunk_sz)
				req.complete.body = true;
			if (req.str_buff.substr(req.body.chunk_sz, 2) != "\r\n")
				throw Error("400");
			if (write(req.body.tmp_fd, req.str_buff.substr(0, req.body.chunk_sz).c_str(), req.body.chunk_sz) < 0)
				throw Error("500", "treatchunked write");
			req.body.read_chunk_sz = true;
			req.str_buff = req.str_buff.substr(req.body.chunk_sz + 2);
		}
	}
	return (false);
}

bool		RequestMap::_treatLength(Request &req)
{
	size_t			cpy_len;

	if (req.body.cont_len < 0)
	{
		if ((req.body.cont_len = utils::stringToSizeT(req.headers.find("content-length")->second)) < 0)
			throw Error("400");
		if ((size_t)req.body.cont_len > req.locInf.clientMaxBodySizeInBytes)
			throw Error("413", "client max body size with content length");
		req.body.tmp_name = "tmp/" + utils::generateTmpName();
		if ((req.body.tmp_fd = open(req.body.tmp_name.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666)) < 0)
			throw Error("500");
	}
	cpy_len = req.body.tmp_len + (ssize_t)req.str_buff.size() < req.body.cont_len ?
		req.str_buff.size() : req.body.cont_len - req.body.tmp_len;
	req.body.tmp_len += cpy_len;
	if (write(req.body.tmp_fd, req.str_buff.c_str(), cpy_len) < 0)
		throw Error("500", "treatlength write");
	req.str_buff = "";
	if (req.body.tmp_len == req.body.cont_len)
	{
		req.complete.body = true;
		return (false);
	}
	return (true);
}

bool		RequestMap::_getBody(const int &fd)
{
	std::map<std::string, std::string>::const_iterator		it;
	Request			&req = _map[fd];

	if (!req.maxSzTested)
	{
		_getServer(fd);
		_getLocation(req);

		req.maxSzTested = true;
	}
	if ((it = req.headers.find("transfer-encoding")) != req.headers.end())
		return (_treatChunked(req, it));
	else if ((it = req.headers.find("content-length")) != req.headers.end())
		return (_treatLength(req));
	else
	{
		req.body.tmp_len = 0;
		req.complete.body = true;
		return (false);
	}
}

void		RequestMap::delReq(int fd)
{
	_map.erase(fd);
}

bool		RequestMap::_getMethod(Request &req)
{
	utils::begTrimN(req.str_buff, "\r\n");
	size_t		found = req.str_buff.find(" ");

	if (req.str_buff.empty())
		return (true);
	if (!utils::isUpper(req.str_buff.substr(0, found)))
		throw Error("400", "should be uppercase");
	req.reqLine.method.append(req.str_buff.substr(0, found));
	req.str_buff = req.str_buff.substr(found == std::string::npos ? req.str_buff.size() : found,
		std::string::npos);
	if (found != std::string::npos)
	{
		if (!req.reqLine.method.size())
			throw Error("400");
		req.complete.method = true;
		return (false);
	}
	return (true);
}

bool		RequestMap::_getUri(Request &req)
{
	utils::begTrimN(req.str_buff, " ");

	size_t		found_space = req.str_buff.find(" ");
	size_t		found = req.str_buff.find(" H");
	std::string	tmp;
	std::string tmp2;

	if (found_space != std::string::npos && req.reqLine.method != "CONNECT" && req.str_buff[0] != '/')
		throw Error("400");
	tmp = req.str_buff.substr(0, found);
	if (found != std::string::npos)
		utils::endTrimN(tmp, " ");
	tmp2 = tmp;
	utils::endTrimN(tmp, " ");
	if (tmp2.size() > MAX_URI_SIZE)
		throw Error("414");
	if (found == std::string::npos)
		return (true);
	if (tmp.empty())
		throw Error("400");
	req.reqLine.uri = tmp;
	req.complete.uri = true;
	_setQueryString(req);
	req.str_buff = req.str_buff.substr(found + 1);
	return (false);
}

void	RequestMap::_setQueryString(Request &req)
{
	size_t	questionMark = req.reqLine.uri.find_first_of('?');

	if (questionMark != std::string::npos)
	{
		req.reqLine.queryString = req.reqLine.uri.substr(questionMark + 1);
		req.reqLine.uri = req.reqLine.uri.substr(0, questionMark);
	}
}

bool		RequestMap::_getVersion(Request &req)
{
	size_t		found = req.str_buff.find("\n");
	size_t		after_point = 0;
	size_t		size;
	char		buff;

	req.reqLine.version.append(req.str_buff.substr(0, found));
	req.str_buff = req.str_buff.substr(found != std::string::npos ? found + 1
		: req.str_buff.size(), std::string::npos);
	if (found != std::string::npos)
	{
		if (!req.reqLine.version.size()
			|| req.reqLine.version[req.reqLine.version.size() - 1] != '\r')
			throw Error("400");
		utils::endTrimN(req.reqLine.version, " \r");
		req.complete.version = true;
		return (false);
	}
	size = req.reqLine.version.size();
	if (req.reqLine.version.compare(0, size < 5 ? size : 5, "HTTP/", size < 5 ? size : 5))
		throw Error("400");
	if (size > 5)
	{
		buff = req.reqLine.version[5];
		if (!utils::isNum(buff))
			throw Error("400");
		else if (buff != '1')
			throw Error("505");
	}
	if (size > 6)
	{
		buff = req.reqLine.version[6];
		if (utils::isNum(buff))
			throw Error("505");
		else if (buff != '.')
			throw Error("400");
	}
	if (size > 7)
	{
		for (size_t i = 7; i < size; ++i)
		{
			char	prevBuff = req.reqLine.version[i - 1];

			buff = req.reqLine.version[i];
			if (i == 7)
			{
				if (utils::isNum(buff))
					++after_point;
				else
					throw Error("400");
			}
			else if (utils::isNum(prevBuff))
			{
				if (utils::isNum(buff))
				{
					if (after_point > 2)
						throw Error("505");
					else
						++after_point;
				}
				else if (buff != ' ' && buff != '\r')
					throw Error("400");
			}
			else if (prevBuff != ' ' || (buff != ' ' && buff != '\r'))
				throw Error("400");
		}
	}
	return (true);
}

bool		RequestMap::_getHeaders(Request &req)
{
	size_t		found;

	if ((found = req.str_buff.find("\r\n")) == 0)
	{
		req.complete.headers = true;
		req.str_buff = req.str_buff.substr(2);
		return (false);
	}
	if ((found = req.str_buff.find("\r\n\r\n")) != std::string::npos)
	{
		std::vector<std::string>	hdrsVect;

		req.complete.headers = true;
		utils::split(hdrsVect, req.str_buff.substr(0, found), "\r\n", utils::LINESPLIT);
		for (size_t i = 0; i < hdrsVect.size(); ++i)
		{
			std::vector<std::string>	keyValue;
			std::string					key;

			utils::split(keyValue, hdrsVect[i], ":", utils::ONESPLIT);
			key = utils::toLowerCase(keyValue[0]);
			utils::trimN(key, " ");
			if (keyValue.size() > 1)
				utils::trimN(keyValue[1], " ");
			req.headers[key] = keyValue.size() > 1 ? keyValue[1] : "";
		}
		req.str_buff = req.str_buff.substr(found + 4);
		return (false);
	}
	return (true);
}

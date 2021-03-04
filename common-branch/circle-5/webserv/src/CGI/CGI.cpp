/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 19:34:31 by adrien            #+#    #+#             */
/*   Updated: 2020/10/22 18:13:53 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

CGI::CGI(Request *rqh,const Client *client):
 _rqh(rqh), _client(client),
 _args(NULL), _env(NULL),
  _tmpFd(-1),
 _state(SHOULD_PARSE_HEADERS),
 _contentLen(0),
 _contentSent(0),
 cgiPipe{-1, -1}
{
}

CGI::~CGI()
{
}

void        CGI::_freeArgsAndEnv(void)
{
	if (_args)
	{
		utils::delete2dArray(_args);
		_args = NULL;
	}
	if (_env)
	{
		utils::delete2dArray(_env);
		_env = NULL;
	}
}

bool		CGI::clean(bool ret)
{
	_freeArgsAndEnv();

	if (_tmpFd != -1)
	{
		close(_tmpFd);
		unlink(_tmpName.c_str());
	}
	if (cgiPipe[P_READ] != -1)
	{
		close(cgiPipe[P_READ]);
		cgiPipe[P_READ] = -1;
	}
	if (cgiPipe[P_WRITE] != -1)
	{
		close(cgiPipe[P_WRITE]);
		cgiPipe[P_WRITE] = -1;
	}

	return ret;
}

std::list<std::string>	initForbiddenHeaders()
{
	std::list<std::string>       list;

	list.push_back("authorization");
	list.push_back("content-type");
	list.push_back("content-length");
	list.push_back("connection");

	return list;
}

std::list<std::string>		CGI::forbiddenHttpHeaders(initForbiddenHeaders());

void						CGI::process(const std::string &executablePath, const std::string &uriRooted)
{
	try
	{
		int	pid;
		_tmpName = "./tmp/" + utils::generateTmpName();
		try {
			_args = _getArgs(executablePath, uriRooted);
			_env = _getEnv(uriRooted);
		}
		catch (const std::bad_alloc &e)
		{
			throw Error("500", "[CGI] bad_alloc");
		}

		if ((_tmpFd = open(_tmpName.c_str(), O_CREAT | O_WRONLY, 0666)) < 0)
			throw Error("500", "[CGI] Opening tmp file.");

		if (pipe(cgiPipe) != 0)
			throw Error("500", "[CGI] pipe");

		if ((pid = fork()) == 0)
		{
			dup2(cgiPipe[P_READ], STDIN_FILENO);
			dup2(_tmpFd, STDOUT_FILENO);
			close(_tmpFd);
			close(cgiPipe[P_READ]);
			close(cgiPipe[P_WRITE]);

			execve(*_args, _args, _env);
			exit(1);
		}
		else if (pid < 0)
			throw Error("500", "[CGI] pid < 0");
		else
		{
			int		cgiStatus = 0;

			close(_tmpFd);
			_tmpFd = -1;
			close(cgiPipe[P_READ]);
			_writeBodyToPipeIn(uriRooted);
			close(cgiPipe[P_WRITE]);

			waitpid(pid, &cgiStatus, 0);
			if (WEXITSTATUS(cgiStatus))
				throw Error("500", "[CGI] failed status");

			_processed = true;
			clean();
		}
	}
	catch (const Error &error)
	{
		clean();
		throw error;
	}
}

void		CGI::_writeBodyToPipeIn(const std::string &uriRooted)
{
	char	buff[BUFFER_SIZE];
	ssize_t	read_ret = 0;

	if (_rqh->getMethod().value != "POST" && _rqh->getMethod().value != "PUT")
	{
		_rqh->setTmpFd(open(uriRooted.c_str(), O_RDONLY));
		if (_rqh->getTmpFd() < 0)
			utils::errnoCheck(true);
	}
	while ((read_ret = _rqh->readBody(buff, BUFFER_SIZE)) > 0)
		if (write(cgiPipe[P_WRITE], buff, read_ret) < 0)
			throw Error("500", "[CGI] write to pipe");
	if (read_ret < 0)
		throw Error("500", "[CGI] read_ret");
}

char **		CGI::_getArgs(const std::string &executablePath, const std::string &uriRooted)
{
	std::list<std::string> args;

	args.push_back(executablePath);
	args.push_back(uriRooted);

	return utils::listTo2dArray(args);
}

char **		CGI::_getEnv(const std::string &uriRooted)
{
	std::list<std::string> 	env;

	_addReqHeadersToEnv(env);
	if (_rqh->getMethod().value == "GET")
	{
		struct stat				fileStat;

		utils::memset(&fileStat, 0, sizeof(fileStat));
		if (stat(uriRooted.c_str(), &fileStat) || !S_ISREG(fileStat.st_mode))
			throw Error("404", "[CGI] stat env");
		env.push_back("CONTENT_LENGTH=" + utils::longToString(fileStat.st_size));
	}
	else
		env.push_back("CONTENT_LENGTH=" + _rqh->getContentLength().value);

	env.push_back("AUTH_TYPE=" + _rqh->getAuthorization().value.type);
	env.push_back("CONTENT_TYPE=" + _rqh->getContentType().value);
	env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	env.push_back("PATH_INFO=" + _rqh->getUri().value);
	env.push_back("PATH_TRANSLATED=" + uriRooted);
	env.push_back("QUERY_STRING=" + _rqh->getRawQueryString());
	env.push_back("REMOTE_ADDR=" + _client->ip);
	env.push_back("REMOTE_IDENT=");
	env.push_back("REMOTE_USER=" + _rqh->getAuthorization().value.credentials);
	env.push_back("REQUEST_METHOD=" + _rqh->getMethod().value);
	env.push_back("REQUEST_URI=" + _rqh->getUri().value);
	env.push_back("SCRIPT_NAME=" + uriRooted.substr(uriRooted.rfind('/')));
	env.push_back("SERVER_NAME=" + _rqh->getHost().value.uri);
	env.push_back("SERVER_PORT=" + utils::longToString(_client->port));
	env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	env.push_back("SERVER_SOFTWARE=" + std::string(SERVER_NAME) + " 1.0");
	env.push_back("REDIRECT_STATUS=1");

	return utils::listTo2dArray(env);
}

void	CGI::_addReqHeadersToEnv(std::list<std::string> &env)
{
	for (std::map<std::string, std::string>::const_iterator it = _rqh->getHeaders().begin(); it != _rqh->getHeaders().end(); ++it)
	{
		if (!_isHeaderToSkip(it->first))
			env.push_back(_formatHttpHeader(it->first, it->second));
	}
}

bool	CGI::_isHeaderToSkip(const std::string &key)
{
	for (std::list<std::string>::iterator it = CGI::forbiddenHttpHeaders.begin(); it != CGI::forbiddenHttpHeaders.end() ; ++it)
		if (*it == key)
			return true;
	return false;
}

std::string			CGI::_formatHttpHeader(const std::string &name, const std::string &value)
{
	std::string result("HTTP_"+ name);

	for (size_t i = 0; i < result.size(); ++i)
	{
		if (result[i] == '-')
			result[i] = '_';
		else
			result[i] = utils::toUpper(result[i]);
	}

	return result + "=" + value;
}

bool	CGI::send(const std::string &statusLine)
{
	try
	{
		char 		buff[BUFFER_SIZE + 1];
		ssize_t		write_ret = 0;
		ssize_t		read_ret = 0;

		if (_tmpFd == -1 && (_tmpFd = open(_tmpName.c_str(), O_RDONLY, 0666)) < 0)
			throw Error("500", "[CGI] open < 0");

		if (_state == SHOULD_PARSE_HEADERS)
		{
			char		buff[BUFFER_SIZE + 1];
			size_t		delFound = std::string::npos;

			if ((read_ret = read(_tmpFd, buff, BUFFER_SIZE)) < 0)
				throw Error("500", "[CGI] send read < 0");
			buff[read_ret] = '\0';
			_bodyBuff.append(buff);

			if ((delFound = _bodyBuff.find("\r\n\r\n")) != std::string::npos)
			{
				_headersBuff = _bodyBuff.substr(0, delFound + 4);
				_bodyBuff = _bodyBuff.substr(delFound + 4);
				_verifyCgiHeaders();
				_prepareHeaders(statusLine);
				_state = IS_SENDING_HEADERS;
			}
		}
		if (_state == IS_SENDING_HEADERS)
		{
			if (_headersBuff.size() && ((write_ret = write(_client->socket, _headersBuff.c_str(), _headersBuff.size())) <= 0))
					throw Error("client disconnected", "[CGI] is sending headers write_ret < 0");
			_headersBuff = _headersBuff.substr(write_ret);
			if (_headersBuff.empty())
			{
				_state = IS_SENDING_BODY;
				if (!_contentLen)
					return clean();
			}
		}
		else if (_state == IS_SENDING_BODY)
		{
			if (_bodyBuff.empty())
			{
				if ((read_ret = read(_tmpFd, buff, BUFFER_SIZE)) < 0)
					throw Error("500", "[CGI] read_ret < 0");
				buff[read_ret] = '\0';
				_bodyBuff.append(buff);
			}
			if (_bodyBuff.size() && (write_ret = write(_client->socket, _bodyBuff.c_str(), _bodyBuff.size())) <= 0)
					throw Error("client disconnected", "[CGI] is sending headers write_ret < 0");
			_bodyBuff = _bodyBuff.substr(write_ret);
			_contentSent += write_ret;
			if (_contentSent == _contentLen)
				return clean();
		}
		return false;
	} catch (const Error &error)
	{
		clean();
		throw error;
	}
}

void	CGI::_verifyCgiHeaders(void)
{
	std::vector<std::string> lines;
	utils::split(lines, _headersBuff, "\r\n", utils::MULTISPLIT);

	for (std::vector<std::string>::iterator it = lines.begin() ; it != lines.end() ; it++)
	{
		if ((*it).empty())
			break;
		std::vector<std::string> fieldNameAndValue;

		utils::split(fieldNameAndValue, *it, ":", utils::ONESPLIT);

		if (fieldNameAndValue.front() == "Status" && fieldNameAndValue.back().find("200") == std::string::npos)
			throw Error(it->size() < 12 ? "500" : it->substr(8, 3), "[CGI] verify cgi headers");
	}
}

void       CGI::_prepareHeaders(const std::string &statusLine)
{
	struct stat stats;

	if (stat(_tmpName.c_str(), &stats) < 0)
		throw Error("500", "[CGI] prepare headers");

	_contentLen = stats.st_size - _headersBuff.size();
	std::string myStatusLine = ((statusLine.size() ? statusLine : "HTTP/1.1 200 OK") + "\r\n");
	_headersBuff.insert(0, "Content-Length: " + utils::longToString(_contentLen) + "\r\n");
	_headersBuff.insert(0, "Date: " + utils::getFormattedTime() + "\r\n");
	_headersBuff.insert(0, "Server: " + std::string(SERVER_NAME) + "\r\n");
	_headersBuff.insert(0, myStatusLine);
}

 bool                                CGI::isProcessed(void)
 {
	return _processed;
 }



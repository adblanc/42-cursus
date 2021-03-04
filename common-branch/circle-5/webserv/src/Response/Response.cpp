/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 11:36:19 by adrien            #+#    #+#             */
/*   Updated: 2020/10/22 18:47:35 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

std::map<std::string, std::string>			Response::createStatusesMap(void)
{
	std::map<std::string, std::string> statuses;

	statuses["200"] = "OK";
	statuses["201"] = "Created";
	statuses["202"] = "Accepted";
	statuses["204"] = "No Content";
	statuses["300"] = "Redirection";
	statuses["301"] = "Moved Permanently";
	statuses["302"] = "Found";
	statuses["400"] = "Bad Request";
	statuses["401"] = "Unauthorized";
	statuses["403"] = "Forbidden";
	statuses["404"] = "Not Found";
	statuses["405"] = "Method Not Allowed";
	statuses["408"] = "Request Timeout";
	statuses["413"] = "Payload Too Large";
	statuses["414"] = "URI Too Long";
	statuses["500"] = "Internal Server Error";
	statuses["501"] = "Not Implemented";
	statuses["502"] = "Bad Gateway";
	statuses["503"] = "Service Unavailable";
	statuses["505"] = "HTTP Version Not Supported";
	return statuses;
}

std::map<std::string, Response::treatment>	Response::createTreatmentsMap(void)
{
	std::map<std::string, treatment>	treats;

	treats["GET"] = &Response::get;
	treats["HEAD"] = &Response::head;
	treats["POST"] = &Response::post;
	treats["PUT"] = &Response::put;
	treats["DELETE"] = &Response::del;
	treats["CONNECT"] = &Response::connect;
	treats["OPTIONS"] = &Response::options;
	treats["TRACE"] = &Response::trace;
	return treats;
}

const std::map<std::string, std::string>			Response::_statuses = Response::createStatusesMap();
const std::map<std::string, Response::treatment>	Response::_treatments = Response::createTreatmentsMap();

MimeTypes Response::_mimeTypes;

Response::Response(Request *req, Server *srv):
_req(req), _srv(srv), _client(req->client),
_cgi(_req, _client), _error(false), _defaultError(false), _state(SHOULD_PARSE_HEADERS), _contentSent(0)
{
	bool		isConnectReq = _req->getMethod().value == "CONNECT";
	setHeader("Date", utils::getFormattedTime());
	setHeader("Server", SERVER_NAME);

	req->setTmpFd(-1);

	if (req->isError())
	{
		setError(req->error.statusCode);
		return ;
	}

	try
	{
		std::map<std::string, treatment>::const_iterator		it;

		it = _treatments.find(req->getMethod().value);
		if (it == _treatments.end())
			throw Error("405", "Response::Response");
		if (!isConnectReq)
		{
			if (req->getLoc()->root.overrided)
				_uriRooted = _req->getLoc()->root.value + "/" + _req->getUri().value.substr(_req->getLoc()->uri.size());
			else
				_uriRooted = _req->getLoc()->root.value + "/" +  _req->getUri().value;

			utils::oneSlash(_uriRooted);

			if (_req->getLoc()->auth.isActive() && !isAuthenticated())
			{
				setHeader("WWW-Authenticate", "Basic realm=" + _req->getLoc()->auth.realm);
					throw Error("401", "Response::Response");
			}
		}
		(*this.*(it->second))();
	}
	catch (const Error &error)
	{
		setError(error.statusCode);
	}
}

Response::~Response()
{
}

void	Response::setError(const std::string &errorCode)
{
	std::string	statusMsg = getStatusMessage(errorCode);

	_statusLine = "HTTP/1.1 " + errorCode + " " + statusMsg;

	if (errorCode == "301")
		setHeader("Location", std::string(_req->getUri().value + "/"));
	else if (errorCode == "405")
		_setAllowHeader();

	const std::string errorPagePath = getErrorPagePath(errorCode);

	_error = true;

	if (errorPagePath.size())
	{
		_uriRooted = (_req->getLoc() ? _req->getLoc()->root.value : _req->getSrvInf()->root) + errorPagePath;
		utils::oneSlash(_uriRooted);

		try
		{
			struct stat		file;
			utils::memset(&file, 0, sizeof(file));

			if (_isReqForCgi())
				return _cgi.process(_cgiExecutablePath, _uriRooted);

			if (stat(_uriRooted.c_str(), &file) || !S_ISREG(file.st_mode))
			{
				setDefaultErrorPage(errorCode, statusMsg);
				return ;
			}
		}
		catch (const Error &error)
		{
			return setDefaultErrorPage(error.statusCode, getStatusMessage(error.statusCode));
		}
		_body.fromFile = true;
		_body.path = _uriRooted;
		setHeader("Content-Type", _mimeTypes.getMimeType(_uriRooted));
	}
	else
		setDefaultErrorPage(errorCode, statusMsg);
}

const std::string					Response::getErrorPagePath(const std::string &errorCode)
{
	if (!_req->getLoc())
	{
		for (std::list<ConfigParser::ErrorPage>::iterator it = _req->getSrvInf()->errorPages.begin(); it != _req->getSrvInf()->errorPages.end(); it++)
		{
			for (std::vector<std::string>::iterator et = it->codes.begin() ; et != it->codes.end() ; et++)
			{
				if (*et == errorCode)
					return (it->uri);
			}
		}
	}
	else
	{
		for (std::list<ConfigParser::ErrorPage>::iterator it = _req->getLoc()->errorPages.begin(); it != _req->getLoc()->errorPages.end(); it++)
		{
			for (std::vector<std::string>::iterator et = it->codes.begin() ; et != it->codes.end() ; et++)
			{
				if (*et == errorCode)
					return (it->uri);
			}
		}
	}

	return ("");
}

void							Response::setDefaultErrorPage(const std::string &errorCode, const std::string &statusMsg)
{
	_defaultError = true;
	std::string body;
	setHeader("Content-Type", "text/html");
	setHeader("Content-Language", LANGAGES);
	body = std::string(ERROR_HTML);

	utils::findAndReplaceAll(body, "{{STATUS_CODE}}", errorCode);
	utils::findAndReplaceAll(body, "{{STATUS_MSG}}", statusMsg);
	utils::findAndReplaceAll(body, "{{SERVER}}", SERVER_NAME);

	_body.str = body;
}

bool							Response::isAuthenticated(void)
{
	for (std::vector<AuthBasic::User>::iterator it = _req->getLoc()->auth.ids.begin() ; it != _req->getLoc()->auth.ids.end() ; it++)
	{
		std::string credentials(it->id + ":" + AuthBasic::base64Decode(it->password));
		if (AuthBasic::base64Encode((const unsigned char *)credentials.c_str(), credentials.size()) == _req->getAuthorization().value.credentials)
			return true;
	}
	return false;
}

bool	Response::getIndex(struct stat &file_stat)
{
	std::string		index;
	bool			index_found = false;

	if (*_uriRooted.rbegin() != '/')
		throw Error("301", "Response::getIndex");

	if (_req->getLoc()->indexes.empty())
		_req->getLoc()->indexes.push_back(INDEX);

	for (std::vector<std::string>::iterator it = _req->getLoc()->indexes.begin(); it != _req->getLoc()->indexes.end() && !index_found; ++it)
	{
		index = _uriRooted + "/" + *it;

		if (stat(index.c_str(), &file_stat))
			utils::errnoCheck();
		else if (S_ISREG(file_stat.st_mode))
		{
			_uriRooted = index;
			index_found = true;
		}
		else
			throw Error("400", "Response::getIndex bad request");
	}
	if (!index_found)
	{
		if (_req->getMethod().value == "POST" || _req->getMethod().value == "PUT")
		{
			_uriRooted += "/" + std::string(INDEX);
			return true;
		}
		if (_req->getLoc()->autoIndex)
			return createAutoIndex();
		else
			throw Error("404", "Response::getIndex not found");
	}
	return (true);
}

void	Response::get(void)
{
	struct stat												file_stat;
	utils::memset(&file_stat, 0, sizeof(file_stat));

	_statusLine = "HTTP/1.1 200 OK";

	if (_isReqForCgi())
	{
		_cgi.process(_cgiExecutablePath, _uriRooted);
		return ;
	}

	if (stat(_uriRooted.c_str(), &file_stat))
		utils::errnoCheck(true);
	else if (S_ISDIR(file_stat.st_mode))
		if (!getIndex(file_stat))
			return ;
	utils::oneSlash(_uriRooted);

	setHeader("Content-Language", LANGAGES);
	setHeader("Content-Type", _mimeTypes.getMimeType(_uriRooted));
	setLastMod(file_stat.st_ctime);
	if (!_body.none)
	{
		_body.fromFile = true;
		_body.path = _uriRooted;
	}
}

void	Response::head(void)
{
	_body.none = true;
	get();
}

void	Response::putPost(int flag)
{
	struct stat												file_stat;
	Request::contentTypeReturn						typ = _req->getContentType();
	std::map<std::string, std::string>::const_iterator		M_type;
	char													buff[BUFFER_SIZE];
	int														fileFd;
	ssize_t													read_ret = 0;

	utils::memset(&file_stat, 0, sizeof(file_stat));
	_statusLine = "HTTP/1.1 200 OK";

	if (_req->getLoc()->uploadStore.size())
		_uriRooted = _req->getLoc()->uploadStore + _req->getUri().value.substr(_req->getLoc()->uri.size());
	if (_isReqForCgi())
	{
		_cgi.process(_cgiExecutablePath, _uriRooted);
		return ;
	}
	if (stat(_uriRooted.c_str(), &file_stat))
	{
		utils::errnoCheck();
		_statusLine = "HTTP/1.1 201 CREATED";
	}
	else if (S_ISDIR(file_stat.st_mode))
		getIndex(file_stat);

	utils::oneSlash(_uriRooted);
	if (flag == O_TRUNC)
		unlink(_uriRooted.c_str());
	if (typ.success)
	{
		std::string		old_uri = _uriRooted;

		_uriRooted = getFileName(_uriRooted) + "." + _mimeTypes.getRevMimeType(typ.value);
		if (old_uri != _uriRooted)
		{
			if (stat(_uriRooted.c_str(), &file_stat))
				utils::errnoCheck();
			else
			{
				_statusLine = "HTTP/1.1 200 OK";
				if (flag == O_TRUNC)
					unlink(_uriRooted.c_str());
			}
		}
	}
	if ((fileFd = open(_uriRooted.c_str(), O_WRONLY | O_CREAT | flag, 0666)) < 0)
		utils::errnoCheck(true);
	while ((read_ret = _req->readBody(buff, BUFFER_SIZE)) > 0)
		if (write(fileFd, buff, read_ret) < 0)
			throw Error("500", "putPost write to fileFd");
	close(fileFd);
	if (read_ret < 0)
		throw Error("500", "Response::putPost");
}

void	Response::post(void)
{
	putPost(O_APPEND);
}

std::string		Response::getFileName(std::string &full_uri)
{
	size_t		last_point_pos = full_uri.rfind(".");
	size_t		last_slash_pos = full_uri.rfind("/");

	return (full_uri.substr(0,
		(last_point_pos != std::string::npos && last_point_pos > last_slash_pos)
		? last_point_pos : std::string::npos));
}

bool			Response::isError(void)
{
	return (_error);
}

std::string		Response::getStatusCode(void)
{
	return _statusLine.size() >= 12 ? _statusLine.substr(9, 3) : std::string();
}

void	Response::put(void)
{
	putPost(O_TRUNC);
}

void	Response::del(void)
{
	struct stat												file_stat;

	utils::memset(&file_stat, 0, sizeof(file_stat));
	_statusLine = "HTTP/1.1 200 OK";

	if (stat(_uriRooted.c_str(), &file_stat))
		utils::errnoCheck(true);
	if (!S_ISREG(file_stat.st_mode))
		throw Error("403", "Response::del");
	if (unlink(_uriRooted.c_str()))
		utils::errnoCheck(true);
	_body.str = DELETE_SUCCESS;
}

void	Response::connect(void)
{
	std::string		uri = _req->getUri().value;
	size_t			pos = uri.find(":");

	if (pos == std::string::npos)
		throw Error("400", "Response::connect");
	std::string		ip = uri.substr(0, pos);
	std::string		port = uri.substr(pos + 1);

	_srv->addNewProxy(_client->socket, ip, port);
	_statusLine = "HTTP/1.1 200 OK";
}

void	Response::options(void)
{
	_statusLine = "HTTP/1.1 200 OK";
	_setAllowHeader();
}

void	Response::_setAllowHeader(void)
{
	std::string			allowed_meth = "GET,HEAD,POST,PUT,DELETE,CONNECT,OPTIONS,TRACE";

	if (_req->getLoc()->methods.size())
	{
		allowed_meth = "";
		for (std::vector<std::string>::iterator it = _req->getLoc()->methods.begin(); it != _req->getLoc()->methods.end(); ++it)
			allowed_meth += (*it + (it + 1 == _req->getLoc()->methods.end() ? "" : ","));
	}
	setHeader("Allow", allowed_meth);
}

void	Response::trace(void)
{
	_statusLine = "HTTP/1.1 200 OK";
	setHeader("Content-Type", "message/http");
	_body.str = (_req->getMethod().value + " "
		+ _req->getUri().value
		+ (_req->getRawQueryString().size() ? ("?" + _req->getRawQueryString()) : "")
		+ " " + _req->getVersion().value + "\r\n"
		+ _req->getRawHeaders());
}

const std::string	Response::getStatusMessage(const std::string &statusCode)
{
	std::map<std::string, std::string>::const_iterator it = _statuses.find(statusCode);

	return it == _statuses.end() ? "" : it->second;
}

void				Response::setLastMod(time_t t)
{
	struct timeval	time;
	struct tm      	timeInfo;
	char			buffer[DATE_BUFFER_SIZE];

	time.tv_sec = t;
	time.tv_usec = 0;
	strptime(utils::longToString(time.tv_sec).c_str(),"%s", &timeInfo);
	strftime(buffer, DATE_BUFFER_SIZE, DATE_FORMAT, &timeInfo);
	setHeader("Last-Modified", buffer);
}

void				Response::setHeader(const std::string &name, const std::string &value)
{
	_headerFields[name] = value;
}

bool				Response::send(bool withBody)
{
	if (_isReqForCgi() && _cgi.isProcessed())
		return _cgi.send(_statusLine);

	ssize_t		write_ret = 0;
	ssize_t		read_ret = 0;

	if (_state == SHOULD_PARSE_HEADERS)
	{
		_headers = _statusLine + "\r\n";
		_setContentLength();

		for (std::map<std::string, std::string>::reverse_iterator it = _headerFields.rbegin(); it != _headerFields.rend(); it++)
			_headers.append(it->first + ": " + it->second + "\r\n");
		_headers += "\r\n";
		_state = IS_SENDING_HEADERS;

		if (_body.fromFile && !_body.none && ((_body.fileFd = open(_body.path.c_str(), O_RDONLY)) < 0))
				throw Error("500", "should parse headers");
	}

	if (_state == IS_SENDING_HEADERS)
	{
		if (_headers.size() && (write_ret = write(_client->socket, _headers.c_str(), _headers.size())) <= 0)
			throw Error("client disconnected", "write_ret <= 0");
		_headers = _headers.substr(write_ret);
		if (_headers.empty())
		{
			_state = IS_SENDING_BODY;
			if (!withBody || _body.none || (_body.fromFile && !_body.fileLen)
				|| (!_body.fromFile && _body.str.empty()))
				return (true);
		}
	}
	else if (_state == IS_SENDING_BODY)
	{
		char	buff[BUFFER_SIZE + 1];

		if (_body.fromFile && _body.str.empty())
		{
			if ((read_ret = read(_body.fileFd, buff, BUFFER_SIZE)) < 0)
				throw Error("500", "read body file fd");
			buff[read_ret] = '\0';
			_body.str.append(buff, read_ret);
		}
		if (_body.str.size() && ((write_ret = write(_client->socket, _body.str.c_str(), _body.str.size())) <= 0))
				throw Error("client disconnected", "is sending body write_ret <= 0");
		_body.str = _body.str.substr(write_ret);
		_contentSent += write_ret;
		if ((_body.fromFile && _contentSent == _body.fileLen)
			|| (!_body.fromFile && _body.str.empty()))
			return (true);
	}
	return (false);
}

void				Response::_setContentLength(void)
{
	struct stat		file_stat;
	utils::memset(&file_stat, 0, sizeof(file_stat));
	if (_body.none)
		return ;
	if (_body.fromFile)
	{
		if (stat(_body.path.c_str(), &file_stat))
			throw Error("500", "Response::setContentLength");
		_body.fileLen = file_stat.st_size;
		setHeader("Content-length", utils::longToString(_body.fileLen));
	}
	else
		setHeader("Content-length", utils::longToString(_body.str.size()));
}

bool   				Response::createAutoIndex(void)
{
    DIR				*dir = NULL;
    struct dirent	*content = NULL;

    if ((dir = opendir(_uriRooted.c_str())) == NULL)
		throw Error("403", "Response::createAutoIndex");

	std::string		path(_req->getUri().value);
	_body.str = LISTING_HTML_1;
    utils::findAndReplaceAll(_body.str, "{{PATH}}", path);
	if (utils::strCmp(path.c_str(), "/"))
		addFileToDirectoryListing("..", getPathBefore(path), true);
    while ((content = readdir(dir)))
	{
        errno = 0;
		if (!utils::strCmp(content->d_name, ".") || !utils::strCmp(content->d_name, "..")) continue;
		addFileToDirectoryListing(content->d_name, std::string(path + content->d_name), content->d_type == DT_DIR);
    }
	utils::errnoCheck(true);
    closedir(dir);

	return (false);
}

void			Response::addFileToDirectoryListing(const std::string &name, const std::string &href, bool isDir)
{
        std::string tag(isDir ? DIRECTORY_HTML : FILE_HTML);

        utils::findAndReplaceAll(tag, "{{NAME}}", name);
        utils::findAndReplaceAll(tag, "{{HREF}}", href);

		_body.str += tag;
}

std::string		Response::getPathBefore(const std::string &path)
{
	return path.substr(0, path.find_last_of('/', path.length() - 2) + 1);
}

bool		Response::_isReqForCgi(void)
{
	if (_defaultError || (_req->getMethod().value != "GET" && _req->getMethod().value != "POST"))
		return false;
	if (_cgiExecutablePath.size())
		return true;
	std::string extension = utils::getFileExtension(_uriRooted);
	std::vector<ConfigParser::Cgi> &cgis = _req->getLoc() ? _req->getLoc()->cgis : _req->getSrvInf()->cgis;
	std::vector<ConfigParser::Cgi>::iterator it = std::find_if(cgis.begin(), cgis.end(), _cgiExtensionMatch(extension));
	if (it == cgis.end())
		return false;
	_cgiExecutablePath = it->executablePath;

	return true;
}

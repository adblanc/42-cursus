/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 14:15:56 by adrien            #+#    #+#             */
/*   Updated: 2020/10/20 17:10:25 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(const std::string &pathToConfigFile): _ctx(MAIN)
{
    int fd;
    int lineCount = 0;

    try
    {
		if ((fd = open(pathToConfigFile.c_str(), O_RDONLY)) < 0)
			throw "Unable to open config file";

		std::string		line;

		while (utils::getLine(fd, line) > 0)
		{
			lineCount++;
			if (isComment(line) || isEmptyLine(line))
				;
			else if (_ctx == MAIN)
				handleMainCtx(line);
			else if (_ctx == SERVER)
				handleServerCtx(line);
			else
				handleLocationCtx(line);
		}
		if (_servers.empty())
			throw "Please specify at least one server block";
		if (_ctx != MAIN)
			throw "Expected token }";
		close(fd);
		sortLocations();
    }
	catch (const char *ex)
    {
        std::string		line;

        while (utils::getLine(fd, line) > 0);
        if (fd != -1)
            close(fd);
        throw std::string(ex) + std::string(" line ") + std::string(utils::longToString(lineCount));
    }
}

ConfigParser::~ConfigParser()
{
}

ConfigParser::serverConfigs		ConfigParser::getServerConfigs() const
{
    return	_servers;
}

void    ConfigParser::handleMainCtx(const std::string &line)
{
    if (isServerContextStart(line))
    {
        ServerInfos		serv;

        _ctx = SERVER;
        _servers.push_back(serv);
    }
    else
        throw "Unexpected token";
}

void    ConfigParser::handleServerCtx(const std::string &line)
{
    if (isContextEnd(line))
    {
        _ctx = MAIN;
        return ;
    }
    if (isLocationContextStart(line))
    {
        _ctx = LOCATION;
        addNewLocationToServer(line);
        return ;
    }
    handleServerDirectives(line);
}

void    ConfigParser::handleServerDirectives(std::string line)
{
        serverConfigs::iterator server = --_servers.end();

        utils::trimN(line);
        if (!isValidLine(line))
            throw "Expected token ;";
        line = line.substr(0, line.size() - 1);
        if (line.substr(0, 7) == "listen ")
            parseHostAndPort(*server, line.substr(7));
        else if (line.substr(0, 5) == "root ")
            server->root = parseRootDirective(line.substr(5));
        else if (line.substr(0, 6) == "index ")
            server->indexes = parseIndexDirective(line.substr(6));
        else if (line.substr(0, 21) == "client_max_body_size ")
            server->clientMaxBodySizeInBytes = parseMaxBodySizeDirective(line.substr(21));
        else if (line.substr(0, 12) == "server_name ")
            server->serverNames = parseServerNameDirective(line.substr(12));
        else if (line.substr(0, 11) == "error_page ")
            parseErrorPagesDirective(server->errorPages, line.substr(11));
        else if (line.substr(0, 10) == "autoindex ")
            server->autoIndex = parseAutoIndexDirective(line.substr(10));
	    else if (line.substr(0, 8) == "use_cgi ")
	    	parseCgiExtensions(server->cgis, line.substr(8));
        else if (line.substr(0, 21) == "auth_basic_user_file ")
            parseAuthBasicFilePath(server->auth, line.substr(21));
        else if (line.substr(0, 11) == "auth_basic ")
            parseAuthBasicRealm(server->auth, line.substr(11));
        else if (line.substr(0, 13) == "upload_store ")
            server->uploadStore = parseUploadStore(line.substr(13));
        else if (line.substr(0, 8) == "connect ")
            server->connect = parseConnect(line.substr(8));
        else
            throw "Unexpected token";
}

void    ConfigParser::handleLocationCtx(const std::string &line)
{
    if (isContextEnd(line))
    {
        _ctx = SERVER;
        return ;
    }
    handleLocationDirectives(line);
}

void    ConfigParser::handleLocationDirectives(std::string line)
{
	serverConfigs::iterator server = --_servers.end();
	std::vector<LocationInfos>::iterator loc = --server->locations.end();

	utils::trimN(line);
	if (!isValidLine(line))
		throw "Expected token ;";
	line = line.substr(0, line.size() - 1);
	if (line.substr(0, 5) == "root ")
		loc->root = LocProperty<std::string>(parseRootDirective(line.substr(5)), true);
	else if (line.substr(0, 6) == "index ")
		loc->indexes = parseIndexDirective(line.substr(6));
	else if (line.substr(0, 21) == "client_max_body_size ")
		loc->clientMaxBodySizeInBytes = parseMaxBodySizeDirective(line.substr(21));
	else if (line.substr(0, 15) == "accept_methods ")
		loc->methods = parseLimitMethodsDirective(line.substr(15));
    else if (line.substr(0, 11) == "error_page ")
        parseErrorPagesDirective(loc->errorPages, line.substr(11));
	else if (line.substr(0, 10) == "autoindex ")
		loc->autoIndex =  parseAutoIndexDirective(line.substr(10));
	else if (line.substr(0, 8) == "use_cgi ")
		parseCgiExtensions(loc->cgis, line.substr(8));
    else if (line.substr(0, 21) == "auth_basic_user_file ")
        parseAuthBasicFilePath(loc->auth, line.substr(21));
    else if (line.substr(0, 11) == "auth_basic ")
        parseAuthBasicRealm(loc->auth, line.substr(11));
    else if (line.substr(0, 13) == "upload_store ")
            loc->uploadStore = parseUploadStore(line.substr(13));
	else
		throw "Unexpected token";
}

void    ConfigParser::parseHostAndPort(ServerInfos &server, std::string value)
{
    std::vector<std::string>	hostPort;
	ConfigParser::Address		address;

    utils::trimN(value);
    utils::split(hostPort, value, ":", utils::ONESPLIT);

    size_t  size = hostPort.size();
    if (size > 2 || !size)
        throw "Please use host:port or port format";
    else if (size == 1)
    {
		address.host = "127.0.0.1";
		address.port = utils::stoi(hostPort[0].c_str());
    }
    else
    {
		address.host = hostPort[0];
		address.port = utils::stoi(hostPort[1].c_str());
    }
	for (ConfigParser::VecAddress::iterator it = server.addresses.begin(); it != server.addresses.end(); ++it)
	{
		if (address.port == it->port)
			throw "You can't use same port on one given server";
	}
	server.addresses.push_back(address);
}

std::string ConfigParser::parseRootDirective(std::string value)
{
    utils::trimN(value);
    return value;
}

std::vector<std::string>    ConfigParser::parseIndexDirective(std::string value)
{
    std::vector<std::string>	result;

    utils::trimN(value);
    utils::split(result, value, " ", utils::MULTISPLIT);
    return result;
}

size_t ConfigParser::parseMaxBodySizeDirective(std::string value)
{
    utils::trimN(value);

    size_t  result = utils::stoi(value.c_str());
    char unit = value[value.size() - 1];

    if (unit == 'k')
        return result * 1000;
    if (unit == 'm')
        return result * 1000 * 1000;
    if (unit < '0' || unit > '9')
        throw "Please specify a correct unit measurement";
    return result;
}

std::vector<std::string> ConfigParser::parseServerNameDirective(std::string value)
{
    utils::trimN(value);
    std::vector<std::string> result;

    utils::split(result, value, " ", utils::MULTISPLIT);
    return result;
}

void    ConfigParser::parseErrorPagesDirective(std::list<ConfigParser::ErrorPage> &errorPages, std::string value)
{
    utils::trimN(value);
    std::vector<std::string>    content;

    utils::split(content, value, " ", utils::MULTISPLIT);

    if (content.size() < 2)
        throw "Please use format code ... uri;";

    ConfigParser::ErrorPage result(content.back());

    content.erase(content.end() - 1);

    result.codes = content;

    errorPages.push_front(result);

}

std::vector<std::string>    ConfigParser::parseLimitMethodsDirective(std::string value)
{
    std::vector<std::string>  result;

    utils::trimN(value);
    utils::split(result, value, " ", utils::MULTISPLIT);

    for (std::vector<std::string>::iterator it = result.begin(); it != result.end() ; it++)
    {
		if (*it != "GET" && *it != "HEAD" &&
			*it != "POST" && *it != "PUT" &&
			*it != "DELETE" &&
			*it != "OPTIONS" && *it != "TRACE")
           throw "Please only enter methods among the following : GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE";
    }
    return result;
}

bool    ConfigParser::parseAutoIndexDirective(const std::string &value)
{
    if (value == "on")
        return true;
    if (value == "off")
        return false;
    throw "Expected on | off";
}


bool   ConfigParser::parseConnect(const std::string &value)
{
    if (value == "on")
        return true;
    if (value == "off")
        return false;
    throw "Expected on | off";
}


void    ConfigParser::parseCgiExtensions(std::vector<ConfigParser::Cgi> &cgis,std::string value)
{
    std::vector<std::string> splitted;

    utils::trimN(value);
    utils::split(splitted, value, " ", utils::MULTISPLIT);

    if (splitted.size() != 2)
        throw "Please use format extension executablePath. Ex: .php /usr/bin/php-cgi";

    if (splitted.front().empty() || splitted.front()[0] != '.')
        throw "Please use format .extension for extension.";

    cgis.push_back(Cgi(splitted.front(), splitted.back()));
}

void     ConfigParser::parseAuthBasicRealm(AuthBasic &auth, std::string value)
{
    utils::trimN(value);

    if (value == "off")
        return auth.turnOff();

    if (value.size() < 3 || (*value.begin()) != '"' ||(*value.rbegin()) != '"')
        throw "Please use format \"string\" | off";

    auth.realm = value;
}

void    ConfigParser::parseAuthBasicFilePath(AuthBasic &auth, std::string value)
{
    utils::trimN(value);

    int fd;

	if ((fd = open(value.c_str(), O_RDONLY)) < 0)
		throw "Please enter a valid file path";

	std::string		line;


	while (utils::getLine(fd, line) > 0)
	{
        if (!isEmptyLine(line))
        {
            std::vector<std::string> splitted;

            utils::split(splitted, line, ":", utils::MULTISPLIT);
            if (splitted.size() < 2)
                continue;

            AuthBasic::User myUser(splitted[0], splitted[1]);

            auth.ids.push_back(myUser);
        }
	}

	close(fd);
}

std::string     ConfigParser::parseUploadStore(std::string value)
{
	struct stat    file_stat;

    utils::trimN(value);

    if (stat(value.c_str(), &file_stat))
        throw "Please enter a valid path to an accessible directory";
    else if (!S_ISDIR(file_stat.st_mode))
        throw "Please enter a valid path to an accessible directory";

    return value;
}

void    ConfigParser::addNewLocationToServer(const std::string &line)
{
    serverConfigs::iterator server = --_servers.end();

    LocationInfos loc(*server);
    loc.uri = parseLocationUri(line);
    server->locations.push_back(loc);
}

bool    ConfigParser::isContextEnd(std::string line)
{
    utils::trimN(line, WHITE_SPACES);
    return line.compare("}") == 0;
}

bool    ConfigParser::isServerContextStart(std::string line)
{
    utils::trimN(line, WHITE_SPACES);
    return line.compare("server {") == 0;
}

bool    ConfigParser::isLocationContextStart(std::string line)
{
    utils::trimN(line, WHITE_SPACES);
    if (line.size() < 8)
        return false;
    if (line.substr(0, 9).compare("location ") != 0)
        return false;
    if (line[line.size() - 1] != '{')
        return false;
    return true;
}

std::string ConfigParser::parseLocationUri(std::string line)
{
    int locationTextLength = 9;

    utils::trimN(line);
    std::string value = line.substr(locationTextLength, line.size() - locationTextLength - 1);
    utils::trimN(value);
    return value;
}

bool    ConfigParser::isValidLine(const std::string &line)
{
    return (!(line.size() && line[line.size() - 1] != ';'));
}

bool    ConfigParser::isEmptyLine(std::string line)
{
    utils::trimN(line);
    return !line.size();
}

bool    ConfigParser::isComment(const std::string &line)
{
    size_t  pos = 0;

    if ((pos = line.find("#")) == std::string::npos)
        return false;
    if (line.substr(0, pos).find_first_not_of("\t ") != std::string::npos)
        return false;
    return true;
}

size_t	ConfigParser::slashCount(const std::string &uri)
{
	size_t			nb = 0;
	size_t			pos;

	for (pos = 0; (pos = uri.find_first_of("/", pos)) != std::string::npos; ++pos)
		++nb;
	return (nb);
}

bool	ConfigParser::locationsComp(const LocationInfos &a, const LocationInfos &b)
{
	size_t			a_nb = slashCount(a.uri);
	size_t			b_nb = slashCount(b.uri);

	if (a_nb > b_nb)
		return (true);
	else if (a_nb == b_nb && a.uri.size() > b.uri.size())
		return (true);
	return (false);
}

void	ConfigParser::sortLocations(void)
{
	for (std::list<ServerInfos>::iterator it = _servers.begin(); it != _servers.end(); ++it)
		std::sort(it->locations.begin(), it->locations.end(), locationsComp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:59:18 by fcadet            #+#    #+#             */
/*   Updated: 2020/10/22 16:53:30 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(void): maxSzTested(false), isDefaultSrvInf(false), client(NULL)
{
	gettimeofday(&age, NULL);
}

Request::~Request()
{
	if (body.tmp_fd >= 0)
		close(body.tmp_fd);
	unlink(body.tmp_name.c_str());
}

bool							Request::isComplete(void) const
{
    return complete.all;
}

bool							Request::isError(void) const
{
    return !error.statusCode.empty();
}

ssize_t							Request::getTmpFd(void)
{
	return (body.tmp_fd);
}

void							Request::setTmpFd(ssize_t fd)
{
	if (body.tmp_fd >= 0)
		close(body.tmp_fd);
	body.tmp_fd = fd;
}

const	std::map<std::string, std::string> 	&Request::getHeaders(void)
{
    return headers;
}

Request::methodReturn	Request::getMethod() const
{
    return (methodReturn(reqLine.method));
}

Request::uriReturn		Request::getUri() const
{
    return (uriReturn(reqLine.uri));
}

Request::versionReturn	Request::getVersion() const
{
    return (versionReturn(reqLine.version));
}

Request::hostReturn		Request::getHost() const
{
	Host			host;

	host.uri = this->host;
	host.port = this->port;
    return (hostReturn(host));
}

Request::authReturn		Request::getAuthorization() const
{
    authReturn					ret;
    std::string					fieldValue = _getStringHeaderValue("authorization").value;
    std::vector<std::string>	typeAndCredentials;

    utils::split(typeAndCredentials, fieldValue, " ", utils::MULTISPLIT);
    if (typeAndCredentials.size() < 2)
        return ret;
    ret.value.type = typeAndCredentials[0];
    ret.value.credentials = typeAndCredentials[1];
    return ret;
}

Request::HandlerReturn<std::string> Request::_getStringHeaderValue(const std::string &name) const
{
    std::map<std::string, std::string>::const_iterator		it;

	it = headers.find(name);
    return (it != headers.end() ? HandlerReturn<std::string>(it->second)
		: HandlerReturn<std::string>(false));
}

Request::userAgentReturn	Request::getUserAgent() const
{
    return _getStringHeaderValue("user-agent");
}

Request::refererReturn	Request::getReferer() const
{
   return _getStringHeaderValue("referer");
}

Request::acceptReturn	Request::getAcceptLanguage() const
{
    return (_parseAcceptHeader("accept-language"));
}

Request::acceptReturn	Request::getAcceptCharset() const
{
    return (_parseAcceptHeader("accept-charsets"));
}

ssize_t							Request::readBody(char *buff, size_t buff_size)
{
	ssize_t				ret = 0;

	if (!body.tmp_len && (getMethod().value == "POST" || getMethod().value == "PUT"))
		return (ret);
	if (body.tmp_fd < 0)
	{
		if ((body.tmp_fd = open(body.tmp_name.c_str(), O_RDONLY)) < 0)
			throw Error("500", "opening file in read body");
	}
	if ((ret = read(body.tmp_fd, buff, buff_size)) < 0)
			throw Error("500", "reading body");
	return (ret);
}

Request::acceptReturn
	Request::_parseAcceptHeader(const std::string &headerName) const
{
    acceptReturn				ret;
    std::string					fieldValue = _getStringHeaderValue(headerName).value;
    std::vector<std::string>	values;

    utils::split(values, fieldValue, ",", utils::MULTISPLIT);
    for (std::vector<std::string>::iterator it = values.begin(); it != values.end(); ++it)
    {
        Accept						infos;
        std::vector<std::string>	parts;

		utils::trimN(*it);
        utils::split(parts, *it, ";", utils::MULTISPLIT);
        infos.type = parts[0];
        infos.quality = _getQuality(parts);
        ret.value.push_back(infos);
    }
    return ret;
}

float				Request::_getQuality(std::vector<std::string> &charset) const
{
    if (charset.size() == 1)
        return (1);
    else
    {
        std::vector<std::string> quality;
        utils::split(quality, charset[1], "=", utils::MULTISPLIT);
        if (quality.size() == 1)
            return (0);
        return utils::stof(quality[1].c_str());
    }
}

Request::contentLengthReturn Request::getContentLength() const
{
	std::map<std::string, std::string>::const_iterator		it;

    // if (getMethod().value != "POST" && getMethod().value != "PUT")
    // {
    //     return contentLengthReturn(false);
    // }

	it = headers.find("content-length");
    return (it != headers.end() ? contentLengthReturn(it->second)
		: contentLengthReturn(false));
}

Request::contentTypeReturn Request::getContentType() const
{
	std::map<std::string, std::string>::const_iterator		it;

	it = headers.find("content-type");
    return (it != headers.end() ? contentTypeReturn(it->second)
		: contentTypeReturn(false));
}

std::string				Request::getRawQueryString() const
{
    return reqLine.queryString;
}

std::string				Request::getRawHeaders(void) const
{
	std::string			result;

	for (std::map<std::string, std::string>::const_reverse_iterator it = headers.rbegin(); it != headers.rend(); ++it)
		result += (it->first + " : " + it->second + "\r\n");
	return (result);
}

ConfigParser::ServerInfos		*Request::getSrvInf()
{
	return (&srvInf);
}

ConfigParser::LocationInfos		*Request::getLoc()
{
	return (&locInf);
}

Request::queryStringReturn		Request::getQueryString() const
{
    std::vector<std::string> splitted;

    if (!reqLine.queryString.length())
        return queryStringReturn(false);

    utils::split(splitted, reqLine.queryString, "&", utils::MULTISPLIT);


    keyValueVec keyValues = _parseKeyValues(splitted);

    return queryStringReturn(keyValues);
}

Request::keyValueVec	            Request::_parseKeyValues(const std::vector<std::string> &keyValues) const
{
     std::vector<utils::pair<std::string, std::string> > result;

    for (std::vector<std::string>::const_iterator it = keyValues.begin(); it != keyValues.end() ; it++)
    {
        std::vector<std::string> keyValue;

        utils::split(keyValue,*it, "=", utils::ONESPLIT);

        if (keyValue.empty())
            break ;

        utils::pair<std::string, std::string> pair(keyValue.front(), (keyValue.size() > 1 ? keyValue.back() : ""));

        result.push_back(pair);
    }

    return result;
}

void							Request::setSrvInf(const ConfigParser::ServerInfos &srvInf)
{
    this->srvInf = srvInf;
}

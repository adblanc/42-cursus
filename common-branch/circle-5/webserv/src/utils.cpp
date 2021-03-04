/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 14:56:59 by fcadet            #+#    #+#             */
/*   Updated: 2020/10/22 17:06:06 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

int		utils::getLine(int fd, std::string &line)
{
	static std::map<int, remainder_t>	remainderMap;

	char					buff[BUFFER_SIZE + 1];
	ssize_t					ret = -2;
	size_t					found;

	if (remainderMap.find(fd) == remainderMap.end())
		remainderMap[fd].str = "";
	while ((found = remainderMap[fd].str.find("\n")) == std::string::npos
		&& (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		remainderMap[fd].str.append(buff);
	}
	if (ret == -1)
	{
		remainderMap.erase(fd);
		return (ret);
	}
	if (!ret)
		remainderMap[fd].eof = true;
	line = remainderMap[fd].str.substr(0, found);
	remainderMap[fd].str = remainderMap[fd].str.substr(found == std::string::npos ? remainderMap[fd].str.size() : found + 1, std::string::npos);
	if (!remainderMap[fd].str.size() && !line.size() && remainderMap[fd].eof)
	{
		remainderMap.erase(fd);
		return (0);
	}
	else
		return (1);
}

std::vector<std::string>	&utils::split(std::vector<std::string> &list,
	const std::string &req, std::string delim, split_t type)
{
	size_t	oldEnd = 0;
	size_t	end = 0;
	size_t	fieldLen;

	while ((end = req.find(delim, oldEnd)) != std::string::npos)
	{
		fieldLen = end - oldEnd;
		if (type != NOEMPTY || fieldLen)
			list.push_back(req.substr(oldEnd, fieldLen));
		oldEnd = end + delim.size();
		if (type == ONESPLIT || (type == LINESPLIT && !fieldLen))
			break ;
	}
	if (req.length() > oldEnd)
		list.push_back(req.substr(oldEnd, req.length()));
	return (list);
}

int		utils::initSockAddr(struct sockaddr_in *addr, std::string ip, unsigned short port)
{
	(void)ip;
	addr->sin_addr.s_addr = inet_addr(ip.c_str());
	if (addr->sin_addr.s_addr == INADDR_NONE)
		return (1);
	addr->sin_family = AF_INET;
	addr->sin_port = utils::ft_htons(port);
	return (0);
}

std::string					utils::ft_inet_ntoa(struct in_addr in)
{
	unsigned char *bytes = (unsigned char *)&in;

	std::string result;

	for (int i = 0 ; i < 3 ; i++)
		result += (longToString(bytes[i]) + ".");
	result += (longToString(bytes[3]));

	return result;
}

void	utils::perror(const char *s)
{
	std::cerr << s << ": " << strerror(errno) << std::endl;
}

int		utils::retError(std::string error, int ret)
{
	std::cerr << "error: " << error << std::endl;
	return (ret);
}

void    utils::exitWithError(char const *error)
{
    utils::perror(error);
	exit_program(EXIT_FAILURE);
}

unsigned short int	utils::ft_htons(unsigned short int hostshort)
{
	return (((hostshort & 0xff00) >> 8) | ((hostshort & 0xff) << 8));
}

void	*utils::memset(void *ptr, int value, size_t num)
{
	char	*mem = (char *)ptr;

	for (size_t i = 0; i < num; ++i)
		mem[i] = value;
	return (ptr);
}

struct timeval		utils::msToTimeval(unsigned int timeOut)
{
	struct timeval	result;

	result.tv_sec = timeOut / 1000;
	result.tv_usec = 0;
	return (result);
}

time_t				utils::timeValToMs(struct timeval tv)
{
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

bool	utils::charInSet(char c, const std::string &charSet)
{
	for (size_t i = 0; i < charSet.size(); ++i)
		if (charSet[i] == c)
			return (true);
	return (false);
}

std::string		&utils::trimN(std::string &str, const std::string &charSet, ssize_t charNb)
{
	begTrimN(str, charSet, charNb);
	endTrimN(str, charSet, charNb);
	return (str);
}

std::string		&utils::begTrimN(std::string &str, const std::string &charSet, ssize_t charNb)
{
	for (; charNb && str.size() && charInSet(*(str.begin()), charSet); --charNb)
		str.erase(0, 1);
	return (str);
}

std::string		&utils::endTrimN(std::string &str, const std::string &charSet, ssize_t charNb)
{
	for (; charNb && str.size() && charInSet(*(str.rbegin()), charSet); --charNb)
		str.resize(str.size() - 1);
	return (str);
}

bool				utils::isUpper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool				utils::isLower(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool				utils::isUpper(const std::string &str)
{
	for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
		if (!isUpper(*it))
			return (false);
	return (true);
}

bool				utils::isNum(char c)
{
	return (c >= '0' && c <= '9');
}

std::string			utils::toLowerCase(const std::string &str)
{
    std::string lowered;

    for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
    {
        if (*it >= 'A' && *it <= 'Z')
            lowered.push_back(*it + 32);
        else
            lowered.push_back(*it);
    }
    return lowered;
}

float utils::stof(const char *s)
{
    float res;
    float fact;

    res = 0;
    fact = 1;

    if (!s)
        return 0;

    if (*s == '-')
    {
        s++;
        fact = -1;
    };
    for (int point_seen = 0; *s; s++)
    {
        if (*s == '.')
        {
            point_seen = 1;
            continue;
        };
        int d = *s - '0';
        if (d >= 0 && d <= 9)
        {
            if (point_seen)
                fact /= 10.0f;
            res = res * 10.0f + (float)d;
        };
    };

    return res * fact;
};

int utils::stoi(const char *s)
{
    int res;
    int fact;

    res = 0;
    fact = 1;

    if (!s)
        return 0;

    if (*s == '-')
    {
        s++;
        fact = -1;
    };
    while (*s)
    {
        int d = *s - '0';
        if (d >= 0 && d <= 9)
            res = res * 10 + d;
        else
            break;
        s++;
    }

    return res * fact;
};

bool		utils::isHex(char c)
{
	return ((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'));
}

ssize_t		utils::stringToSizeT(const std::string &nb, bool hexa)
{
	ssize_t		ret = 0;

	for (size_t i = 0; i < nb.size(); ++i)
	{
		if (hexa ? !isHex(nb[i]) : !isNum(nb[i]))
			return (-1);
		ret *= hexa ? 16 : 10;
		ret += hexa ? (nb[i] >= '0' && nb[i] <= '9' ? nb[i] - '0' : nb[i] - 'a' + 10)
			: (nb[i] - '0');
	}
	return (ret);
}

std::string utils::longToString(long long value)
{
  std::string output;
  std::string sign;

  if(value < 0)
  {
    sign + "-";
    value = -value;
  }

  while(output.empty() || (value > 0))
  {
    output.insert(output.begin(), value % 10 + '0');
    value /= 10;
  }

  return (sign + output);
}

void						utils::findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	size_t pos = data.find(toSearch);

	while( pos != std::string::npos)
	{
		data.replace(pos, toSearch.size(), replaceStr);
		pos =data.find(toSearch, pos + replaceStr.size());
	}
}

int							utils::strCmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

const std::string			utils::getFdContent(const int &fd)
{
	std::string			content;
	std::string			line;

	while (getLine(fd, line) > 0)
		content += line;

	return content;
}

void						utils::oneSlash(std::string &uri)
{
	for (size_t pos; (pos = uri.find("//")) != std::string::npos; uri.erase(pos, 1))
		;
}

const std::string			&utils::generateTmpName(ssize_t rec_pos)
{
	static std::string		name(".tmp");
	size_t					pos = rec_pos < 0 ? name.find(".") : (size_t)rec_pos;

	if (name[pos] == '.')
	{
		if (!pos)
		{
			name.insert(pos, "0");
			return (name);
		}
		else
			--pos;
	}
	if (isNum(name[pos]))
		name[pos] = (name[pos] == '9' ? 'A' : name[pos] + 1);
	else if (name[pos] == 'Z')
	{
		name[pos] = '0';
		if (!pos)
			name.insert(pos, "0");
		else
			generateTmpName(pos - 1);
	}
	else
		++name[pos];
	return (name);
}

char	*utils::str_cpy(char *dst, const char *src)
{
	char	*save;

	save = dst;
	if (!src || !dst)
		return (dst);
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (save);
}

int		utils::initSockAddr(struct sockaddr_in *addr, std::string ip, std::string port)
{
	ssize_t			prt = utils::stringToSizeT(port);

	addr->sin_addr.s_addr = inet_addr(ip.c_str());
	if (addr->sin_addr.s_addr == INADDR_NONE)
		return (1);
	addr->sin_family = AF_INET;
	if (prt < 0 || prt > 65535)
		return (2);
	addr->sin_port = ft_htons(prt);
	return (0);
}

bool	utils::isAlNum(char c)
{
	if (isNum(c) || ((c >= 'A' && c <= 'Z')
	|| (c >= 'a' && c <= 'z')))
		return (true);
	return (false);
}

bool 	utils::isBase64(unsigned char c)
{
	return (utils::isAlNum(c) || (c == '+') || (c == '/'));
}

void	utils::errnoCheck(bool throw_404)
{
	if (!errno)
		return ;
	else if (errno == EACCES)
		throw Error("403", "errnocheck");
	else if (errno == EFAULT)
		throw Error("400", "errnocheck");
	else if (errno == ELOOP || errno == ENOMEM)
		throw Error("500", "errnocheck");
	else if (errno == ENAMETOOLONG)
		throw Error("414", "errnocheck");
	else if (throw_404 && (errno == ENOENT || errno == ENOTDIR))
		throw Error("404", "errnocheck");
	else if (!throw_404)
		return ;
	else
		throw Error("500", "errnocheck");
}

bool	utils::isTelnetEnd(const std::string &buffer)
{
	char endChars[] = {-1, -12, -1, -3, 6, 0};

	if (buffer.find(endChars) != std::string::npos)
		return true;
	return false;
}

char		*utils::strdup(const char *s1)
{
	size_t	length;
	char	*ptr;

	length = std::string(s1).size();

	ptr = new char[sizeof(char) * length + 1];
	ptr = strcpy(ptr, s1);

	return (ptr);
}

char	**utils::listTo2dArray(const std::list<std::string> &list)
{
	char **result;
	char **ref;

	result = new char*[list.size() + 1];

	ref = result;

	for (std::list<std::string>::const_iterator it = list.begin() ; it != list.end() ; it++)
	{
		*result = strdup(it->c_str());
		result++;
	}
	*result = NULL;

	return ref;
}

void	utils::delete2dArray(char **array)
{
	for (size_t i = 0; array[i] ; i++) {
		delete[] array[i];
	}

	delete[] array;
}

std::string						utils::getFileExtension(const std::string &path)
{
	size_t		pointIndex;
	size_t		slashIndex;

	if (!path.size())
		return "";

	pointIndex = path.rfind(".");
	slashIndex = path.rfind("/");

	if (pointIndex == std::string::npos || slashIndex > pointIndex)
        return "";

	return path.substr(pointIndex);
}

char								utils::toUpper(char c)
{
	if (isLower(c))
		c -= 32;
	return (c);
}

std::string							utils::getFormattedTime(void)
{
	struct timeval	time;
	struct tm      	timeInfo;
	char buffer [DATE_BUFFER_SIZE];

	if (gettimeofday(&time, NULL) < 0)
		throw Error("500", "gettimeofday()");
	strptime(utils::longToString(time.tv_sec).c_str(),"%s", &timeInfo);
	strftime(buffer, DATE_BUFFER_SIZE, DATE_FORMAT, &timeInfo);

	return buffer;
}




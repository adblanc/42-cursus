/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:07:42 by fcadet            #+#    #+#             */
/*   Updated: 2020/10/19 17:49:23 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "headers.hpp"
# include "Error/Error.hpp"

namespace utils
{

	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(T1()), second(T2()){};
		template <class U, class V>
			pair(const pair<U, V> &pr) : first(pr.first), second(pr.second){};
		pair(const first_type &a, const second_type &b) : first(a), second(b){};
	};

	typedef enum		split_e
	{
		ONESPLIT,
		LINESPLIT,
		MULTISPLIT,
		NOEMPTY
	}					split_t;

	int							getLine(int fd, std::string &line);
	int							initSockAddr(struct sockaddr_in *addr, std::string ip,
		unsigned short port);
	std::string					ft_inet_ntoa(struct in_addr in);
	void						perror(const char *s);
	void			    		exitWithError(char const *error);
	unsigned short int			ft_htons(unsigned short int hostshort);
	void						*memset(void *ptr, int value, size_t num);
	struct timeval				msToTimeval(unsigned int timeOut);
	time_t						timeValToMs(struct timeval tv);
	int							retError(std::string error, int ret);
	std::vector<std::string>	&split(std::vector<std::string> &list, const std::string &req, std::string delim, split_t type);
	bool						charInSet(char c, const std::string &charSet);
	std::string					&trimN(std::string &str, const std::string &charSet = WHITE_SPACES,
		ssize_t charNb = -1);
	std::string					&begTrimN(std::string &str,
		const std::string &charSet = WHITE_SPACES, ssize_t charNb = -1);
	std::string					&endTrimN(std::string &str,
		const std::string &charSet = WHITE_SPACES, ssize_t charNb = -1);
	bool						isUpper(char c);
	bool						isUpper(const std::string &str);
	bool						isLower(char c);
	bool						isNum(char c);
	bool						isAlNum(char c);
	bool						isBase64(unsigned char c);
	bool						isHex(char c);
	std::string					toLowerCase(const std::string &str);
	float						stof(const char *);
	int							stoi(const char *);
	ssize_t						stringToSizeT(const std::string &nb, bool hexa = false);
	std::string 				longToString(long long value);
	void 						findAndReplaceAll(std::string & data, std::string toSearch,
		std::string replaceStr);
	int							strCmp(const char *s1, const char *s2);

	const std::string			getFdContent(const int &fd);
	void						oneSlash(std::string &uri);
	char						*str_cpy(char *dst, const char *src);
	const std::string			&generateTmpName(ssize_t rec_pos = -1);
	int							initSockAddr(struct sockaddr_in *addr, std::string ip, std::string port);

	void						errnoCheck(bool throw_404 = false);

	bool						isTelnetEnd(const std::string &buffer);
	char						*strdup(const char *s1);
	char						**listTo2dArray(const std::list<std::string> &list);
	void						delete2dArray(char **array);

	std::string					getFileExtension(const std::string &path);

	std::string					getFormattedTime(void);

	char						toUpper(char c);

	template <typename T, typename T2>
	typename T::const_iterator
	mapReverseFind(const T &map, const T2 &value)
	{
		typename T::const_iterator	it;

		for (it = map.begin(); it != map.end(); ++it)
			if (it->second == value)
				return (it);
		return (map.end());
	}

	struct	remainder_t
	{
		remainder_t(void) : str(""), eof(false) {}

		std::string		str;
		bool			eof;
	};
}

#endif

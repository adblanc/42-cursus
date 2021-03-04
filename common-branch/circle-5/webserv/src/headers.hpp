/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:07:32 by fcadet            #+#    #+#             */
/*   Updated: 2020/10/22 17:05:47 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_HPP
# define HEADERS_HPP

# define PROXY_ACTIVE		true
# define MAX_HOST_NB		500
# define REQ_TIMEOUT		120000
# define SLEEP_TIME			10
# define BUFFER_SIZE    	1000000
# define MAX_URI_SIZE		50
# define WHITE_SPACES		"\t "
# define MAX_BODY_SIZE		100000000
# define DEFAULT_TYPE   	"txt"
# define ENV            	"development"
# define DATE_FORMAT		"%a, %d %b %Y %H:%M:%S GMT"
# define DATE_BUFFER_SIZE	80

enum {P_READ, P_WRITE};
enum STATE {SHOULD_PARSE_HEADERS, IS_SENDING_HEADERS, IS_SENDING_BODY};

# define INDEX			"index.html"
# define SERVER_NAME	"DarkServerOfTheDeepBlackShadow"
# define TRANS_ENC		"identity"
# define LANGAGES		"en, fr"

# define DEFAULT_ROOT   "./data"

# define LISTING_HTML_1 "<html><head><title>Index of {{PATH}}</title><style> body{background-color:#f7fafc;margin:0;padding:0;outline:0;} h1{text-align:center;color:#1a202c;margin-top:25px;} .header{border-bottom:thin solid #718096;} ul{list-style-type:none;padding-left:10%;padding-top:5%;} li{text-decoration:none;display:block;margin-bottom:10px;} </style></head><body> <div class=\"header\"><h1>Index of {{PATH}}</h1></div><ul>"
# define LISTING_HTML_2 "</ul></body></html>"
# define FILE_HTML      "<li><a href=\"{{HREF}}\">{{NAME}}</a></li>"
# define DIRECTORY_HTML "<li><a href=\"{{HREF}}\">&#128193 {{NAME}}</a></li>"
# define DELETE_SUCCESS	"<html><body><h1>File deleted.</h1></body></html>"
# define ERROR_HTML		"<html><head><title>{{STATUS_CODE}} {{STATUS_MSG}}</title></head><body bgcolor=\"white\"><center><h1>{{STATUS_CODE}} {{STATUS_MSG}}</h1></center><hr><center>{{SERVER}}</center></body></html>"


# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"
# define COLOR_END	"\033[0m"
# define UNDERLINE	"\033[4m"

# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <time.h>
# include <dirent.h>
# include <arpa/inet.h>
# include <string>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <iostream>
# include <vector>
# include <map>
# include <list>
# include <algorithm>
# include "utils.hpp"

void		exit_program(int n);

#endif

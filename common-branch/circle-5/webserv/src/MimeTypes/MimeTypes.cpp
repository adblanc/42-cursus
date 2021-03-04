/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeTypes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:05:24 by adrien            #+#    #+#             */
/*   Updated: 2020/09/25 17:38:50 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MimeTypes.hpp"

std::map<std::string, std::string>			MimeTypes::createMIMETypes(void)
{
	std::map<std::string, std::string> MIMETypes;

	MIMETypes["aac"] = "audio/aac";
	MIMETypes["abw"] = "application/x-abiword";
	MIMETypes["arc"] = "application/octet-stream";
	MIMETypes["avi"] = "video/x-msvideo";
	MIMETypes["azw"] = "application/vnd.amazon.ebook";
	MIMETypes["bin"] = "application/octet-stream";
	MIMETypes["bmp"] = "image/bmp";
	MIMETypes["bz"] = "application/x-bzip";
	MIMETypes["bz2"] = "application/x-bzip2";
	MIMETypes["csh"] = "application/x-csh";
	MIMETypes["css"] = "text/css";
	MIMETypes["csv"] = "text/csv";
	MIMETypes["doc"] = "application/msword";
	MIMETypes["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	MIMETypes["eot"] = "application/vnd.ms-fontobject";
	MIMETypes["epub"] = "application/epub+zip";
	MIMETypes["gz"] = "application/gzip";
	MIMETypes["gif"] = "image/gif";
	MIMETypes["html"] = "text/html";
	MIMETypes["ico"] = "image/x-icon";
	MIMETypes["ics"] = "text/calendar";
	MIMETypes["jar"] = "application/java-archive";
	MIMETypes["jpeg"] = "image/jpeg";
	MIMETypes["jpg"] = "image/jpeg";
	MIMETypes["js"] = "application/javascript";
	MIMETypes["json"] = "application/json";
	MIMETypes["jsonld"] = "application/ld+json";
	MIMETypes["mid"] = "audio/midi";
	MIMETypes["midi"] = "audio/midi";
	MIMETypes["mjs"] = "text/javascript";
	MIMETypes["mp3"] = "audio/mpeg";
	MIMETypes["mpeg"] = "video/mpeg";
	MIMETypes["mpkg"] = "application/vnd.apple.installer+xml";
	MIMETypes["odp"] = "application/vnd.oasis.opendocument.presentation";
	MIMETypes["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	MIMETypes["odt"] = "application/vnd.oasis.opendocument.text";
	MIMETypes["oga"] = "audio/ogg";
	MIMETypes["ogv"] = "video/ogg";
	MIMETypes["ogx"] = "application/ogg";
	MIMETypes["opus"] = "audio/opus";
	MIMETypes["otf"] = "font/otf";
	MIMETypes["png"] = "image/png";
	MIMETypes["pdf"] = "application/pdf";
	MIMETypes["php"] = "application/x-httpd-php";
	MIMETypes["ppt"] = "application/vnd.ms-powerpoint";
	MIMETypes["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	MIMETypes["rar"] = "application/x-rar-compressed";
	MIMETypes["rtf"] = "application/rtf";
	MIMETypes["sh"] = "application/x-sh";
	MIMETypes["svg"] = "image/svg+xml";
	MIMETypes["swf"] = "application/x-shockwave-flash";
	MIMETypes["tar"] = "application/x-tar";
	MIMETypes["tif"] = "image/tiff";
	MIMETypes["tiff"] = "image/tiff";
	MIMETypes["ts"] = "application/typescript";
	MIMETypes["ttf"] = "font/ttf";
	MIMETypes["txt"] = "text/plain";
	MIMETypes["vsd"] = "application/vnd.visio";
	MIMETypes["wav"] = "audio/x-wav";
	MIMETypes["weba"] = "audio/webm";
	MIMETypes["webm"] = "video/webm";
	MIMETypes["webp"] = "image/webp";
	MIMETypes["woff"] = "font/woff";
	MIMETypes["woff2"] = "font/woff2";
	MIMETypes["xhtml"] = "application/xhtml+xml";
	MIMETypes["xls"] = "application/vnd.ms-excel";
	MIMETypes["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	MIMETypes["xml"] = "application/xml";
	MIMETypes["xul"] = "application/vnd.mozilla.xul+xml";
	MIMETypes["zip"] = "application/zip";
	MIMETypes["3gp"] = "video/3gpp";
	MIMETypes["3g2"] = "video/3gpp2";
	MIMETypes["7z"] = "application/x-7x-compressed";
	return MIMETypes;
}

const std::map<std::string, std::string>			MimeTypes::_data = MimeTypes::createMIMETypes();

std::string		MimeTypes::getMimeType(const std::string &filePath)
{
	std::map<std::string, std::string>::const_iterator		M_type;
	size_t													last_point_pos;
	size_t													last_slash_pos;

	last_point_pos = filePath.rfind(".");
	last_slash_pos = filePath.rfind("/");
	M_type = (last_point_pos != std::string::npos && (last_slash_pos == std::string::npos || last_point_pos > last_slash_pos))
		? _data.find(filePath.substr(last_point_pos + 1)) : _data.end();
	if (M_type == _data.end())
		M_type = _data.find(DEFAULT_TYPE);

	return M_type->second;
}

std::string		MimeTypes::getRevMimeType(const std::string &contType)
{
	std::map<std::string, std::string>::const_iterator	M_type;

	M_type = utils::mapReverseFind<std::map<std::string, std::string>, std::string>(_data, contType);
	return (M_type != _data.end() ? M_type->first : DEFAULT_TYPE);
};

MimeTypes::MimeTypes(void)
{

};

MimeTypes::MimeTypes(const MimeTypes &src)
{
    *this = src;
};

MimeTypes::~MimeTypes()
{

};

MimeTypes &MimeTypes::operator= (const MimeTypes &rhs)
{
    if (this != &rhs)
    {

    }
    return (*this);
};

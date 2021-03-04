/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 14:15:44 by adrien            #+#    #+#             */
/*   Updated: 2020/10/20 17:06:22 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include "../headers.hpp"
# include "../AuthBasic/AuthBasic.hpp"

class ConfigParser
{

    public:

		template <typename T>
		struct LocProperty
		{
			LocProperty(void):
			value(), overrided(false)
			{
			}
			LocProperty(const T &value):
			value(value), overrided(false)
			{
			}

			LocProperty(const T &value, bool overrided):
			value(value), overrided(overrided)
			{
			}

			T value;
			bool overrided;
		};

		struct Address
		{
			Address(void) : host(), port() {}
			Address(std::string host, size_t port): host(host), port(port) {}

			std::string		host;
			size_t			port;
		};

		struct ErrorPage
		{
			ErrorPage(std::string uri): uri(uri) {}
			std::vector<std::string>	codes;
			std::string					uri;
		};

		struct ServerInfos;

		struct Cgi {
			Cgi(const std::string &extension, const std::string &executablePath)
			: extension(extension), executablePath(executablePath) {}

			std::string extension;
			std::string executablePath;
		};

		struct LocationInfos
		{
			LocationInfos(void) {}
			LocationInfos(const ServerInfos &server) : root(server.root),
				indexes(server.indexes),
				clientMaxBodySizeInBytes(server.clientMaxBodySizeInBytes),
				errorPages(server.errorPages),
				cgis(server.cgis),
				auth(server.auth),
				uploadStore(server.uploadStore),
				autoIndex(server.autoIndex) {}

			std::string					uri;
			std::vector<std::string>	methods;
			LocProperty<std::string>	root;
			std::vector<std::string>	indexes;
			size_t						clientMaxBodySizeInBytes;
			std::list<ErrorPage>		errorPages;
			std::vector<Cgi>			cgis;
			AuthBasic					auth;
			std::string					uploadStore;
			bool						autoIndex;
		};

		struct ServerInfos
		{
			ServerInfos(void): root(DEFAULT_ROOT),
				clientMaxBodySizeInBytes(MAX_BODY_SIZE), autoIndex(false), connect(true) {}

			std::vector<Address>		addresses;
			std::string					root;
			std::vector<std::string>	serverNames;
			std::vector<std::string>	indexes;
			size_t						clientMaxBodySizeInBytes;
			bool						autoIndex;
			std::list<ErrorPage>		errorPages;
			std::vector<Cgi>			cgis;
			AuthBasic					auth;
			std::vector<LocationInfos>	locations;
			std::string					uploadStore;
			bool						connect;
		};

		typedef std::vector<Address>		VecAddress;
        typedef std::list<ServerInfos>		serverConfigs;

        ConfigParser(const std::string &pathToConfigFile);
        ~ConfigParser();

        serverConfigs						getServerConfigs() const;

    private:
		enum Context
		{
			MAIN,
			SERVER,
			LOCATION
		};


		void                        handleMainCtx(const std::string &line);
		void                        handleServerCtx(const std::string &line);
		void                        handleLocationCtx(const std::string &line);
		void                        handleServerDirectives(std::string line);
		void                        handleLocationDirectives(std::string line);
		void                        addNewLocationToServer(const std::string &line);
		void                        parseHostAndPort(ServerInfos &server, std::string value);
		std::string                 parseRootDirective(std::string value);
		std::vector<std::string>    parseIndexDirective(std::string value);
		std::vector<std::string>    parseLimitMethodsDirective(std::string value);
		size_t                      parseMaxBodySizeDirective(std::string value);
		std::vector<std::string>   	parseServerNameDirective(std::string value);
		void					    parseCgiExtensions(std::vector<Cgi> &cgis, std::string value);
		void						parseAuthBasicRealm(AuthBasic &auth, std::string value);
		void						parseAuthBasicFilePath(AuthBasic &auth, std::string value);
		std::string                 parseUploadStore(std::string value);
		bool                        parseAutoIndexDirective(const std::string &value);
		bool                        parseConnect(const std::string &value);
		void						parseErrorPagesDirective(std::list<ErrorPage> &errorPages, std::string value);
		std::string                 parseLocationUri(std::string line);
		bool                        isComment(const std::string &line);
		bool                        isEmptyLine(std::string line);
		bool                        isValidLine(const std::string &line);
		bool                        isContextEnd(std::string line);
		bool                        isServerContextStart(std::string line);
		bool                        isLocationContextStart(std::string line);

		static size_t				slashCount(const std::string &uri);
		static bool					locationsComp(const LocationInfos &a, const LocationInfos &b);
		void						sortLocations(void);

		Context                     _ctx;
		serverConfigs               _servers;
};

#endif

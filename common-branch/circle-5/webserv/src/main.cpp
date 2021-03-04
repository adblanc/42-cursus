/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:22:27 by fcadet            #+#    #+#             */
/*   Updated: 2020/10/22 17:05:35 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"

static Server							*server = NULL;
static ConfigParser						*config = NULL;
static ConfigParser::serverConfigs		*configs = NULL;

void	catch_sigpipe(int n)
{
	(void)n;
}

void	exit_program(int n)
{
	if (config)
		config->~ConfigParser();
	if (configs)
		configs->~list<ConfigParser::ServerInfos>();
	if (server)
		server->~Server();
	exit(n);
}

void	checkIfRunning(void)
{
	struct stat running;
	utils::memset(&running, 0, sizeof(running));
	int fd;

	if (stat("./tmp/.running", &running) < 0)
	{
		if ((fd = open("./tmp/.running", O_CREAT | O_WRONLY | O_TRUNC, 0666) < 0))
			utils::exitWithError("Server init");
		close(fd);
	}
	else
	{
		std::cerr << "Server is already running" << std::endl;
		exit_program(1);
	}
}

int		main(int ac, char **av)
{
	try
	{
		ConfigParser			conf(ac > 1 ? av[1] : "./conf/tester.conf");
		config = &conf;

		ConfigParser::serverConfigs	confs = conf.getServerConfigs();
		configs = &confs;

		checkIfRunning();

		Server					srv(confs);
		server = &srv;

		signal(SIGPIPE, catch_sigpipe);
		signal(SIGINT, exit_program);

		srv.run();
	}
	catch (std::string &e)
	{
		std::cerr << e << std::endl;
	}
	return (0);
}

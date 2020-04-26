/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:50:09 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/17 17:32:55 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

bool	isArgsValid(char **av)
{
	std::string s;

	s = av[2];
	if (s.empty())
		return (false);
	s = av[3];
	if (s.empty())
		return (false);
	return (true);
}

void	searchAndReplace(char **av)
{
	std::string		fileName;
	std::string		line;
	std::string		toReplace;
	std::string		wordReplacement;
	size_t			length_ToReplace;

	toReplace = av[2];
	length_ToReplace = toReplace.length();
	wordReplacement = av[3];
	fileName = av[1];
	fileName.append(".replace");
	std::ifstream	fsIn(av[1]);
		if (!fsIn)
		{
			std::cout << "Problem while opening " << av[1] << std::endl;
			return ;
		}
	std::ofstream	fsOut(fileName);
		if (!fsOut)
		{
			std::cout << "Problem while opening " << fileName << std::endl;
			return ;
		}
	while (getline(fsIn, line))
	{
		while (true)
		{
			size_t pos = line.find(toReplace);
			if (pos != std::string::npos)
				line.replace(pos, length_ToReplace, wordReplacement);
			else
				break ;
		}
		fsOut << line << std::endl;
	}

}

int main(int ac, char **av)
{
	if (ac == 4)
	{
		if (!isArgsValid(av))
			std::cout << "Strings used for search & replace should not be empty." << std::endl;
		else
			searchAndReplace(av);
	}
	else
		std::cout << "Please pass 3 arguments." << std::endl;
	return (0);
}

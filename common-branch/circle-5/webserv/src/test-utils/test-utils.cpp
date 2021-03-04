/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 18:04:52 by adrien            #+#    #+#             */
/*   Updated: 2020/10/08 17:14:17 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test-utils.hpp"

void test::display(const char *text, const char *color)
{
    std::cout << color << text << COLOR_END << std::endl;
}

void test::display_success(const char *text)
{
    std::cout << "  ";
    std::cout << BLUE << text
              << GREEN << " OK"
              << COLOR_END << std::endl;
}

Request         test::simulateReq(RequestMap &reqMap, int fd)
{
    while (!reqMap.getRequest(fd).isComplete())
    {
        try {
            reqMap.parseReqFrom(fd);
        } catch (const Error &error) {
            reqMap.getRequest(fd).error = error;
            break;
        }
    }

    return reqMap.getRequest(fd);
}

void            test::closeFd(int fd, RequestMap &reqMap)
{
    reqMap.delReq(fd);
    reqMap.delRsp(fd);
    reqMap.eraseClient(fd);
    close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requestreq.test.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 19:15:29 by adrien            #+#    #+#             */
/*   Updated: 2020/09/15 19:15:38 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test-utils/test-utils.hpp"

static int  getReqFd(const std::string &reqName)
{
    int fd;

    if ((fd = open((REQUESTS_PATH + std::string(reqName)).c_str(), O_RDONLY)) < 0)
        assert(0);
    
    return fd;
}

static void test_req_host_default_port(RequestMap &reqMap)
{
    int fd = getReqFd("default_port");

    Request req = test::simulateReq(reqMap, fd);

    assert(req.getHost().success == true);
    assert(req.getHost().value.uri == "www.example.org");
    assert(req.getHost().value.port == 80);

    test::display_success("Default port");
    test::closeFd(fd, reqMap);
}

static void test_req_no_host(RequestMap &reqMap)
{
    int fd = getReqFd("no_host");

    Request req = test::simulateReq(reqMap, fd);

    Response rsp = reqMap.getResponse(fd, NULL);

    assert(rsp.getStatusCode() == "400");

    test::display_success("No host");
    test::closeFd(fd, reqMap);
}

static void test_req_get(RequestMap &reqMap)
{
    int fd = getReqFd("get");

    Request req = test::simulateReq(reqMap, fd);

    assert(req.getMethod().success == true);
    assert(req.getMethod().value == "GET");

    assert(req.getUri().success == true);
    assert(req.getUri().value == "/");

    assert(req.getVersion().success == true);
    assert(req.getVersion().value == "HTTP/1.1");

    assert(req.getUserAgent().success == true);
    assert(req.getUserAgent().value == "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/604.5.6 (KHTML, like Gecko) Version/11.0.3 Safari/604.5.6");

    assert(req.getAcceptLanguage().success == true);
    assert(req.getAcceptLanguage().value.front().type == "en-us");
    assert(req.getAcceptLanguage().value.front().quality == 1);

    assert(req.getHost().success == true);
    assert(req.getHost().value.uri == "localhost");
    assert(req.getHost().value.port == 8080);

    test::display_success("Headers");
    test::closeFd(fd, reqMap);
}

static void     test_query_string(RequestMap &reqMap)
{
    int fd = getReqFd("get");

    Request req = test::simulateReq(reqMap, fd);

   Request::queryStringReturn queryString = req.getQueryString();

    assert(queryString.success);

    assert(queryString.value.size() == 3);

    assert(queryString.value[0].first == "a");
    assert(queryString.value[0].second == "b");

    assert(queryString.value[1].first == "cc");
    assert(queryString.value[1].second == "dd");

    assert(queryString.value[2].first == "eee");
    assert(queryString.value[2].second == "fff");

    test::display_success("Query string");
    test::closeFd(fd, reqMap);
}

static void     test_empty_query_string(RequestMap &reqMap)
{
    int fd = getReqFd("get_2");

    Request req = test::simulateReq(reqMap, fd);

    Request::queryStringReturn queryString = req.getQueryString();

    assert(!queryString.success);

    assert(queryString.value.empty());

    test::display_success("Empty query string");

    test::closeFd(fd, reqMap);
}

void    test::test_request()
{
    ConfigParser parser(CONFIGS_PATH + std::string("one_server.conf"));
    ConfigParser::serverConfigs configs = parser.getServerConfigs();
    RequestMap reqMap(configs);

    test_req_host_default_port(reqMap);
    test_req_no_host(reqMap);
    test_req_get(reqMap);
    test_query_string(reqMap);
    test_empty_query_string(reqMap);
    
}
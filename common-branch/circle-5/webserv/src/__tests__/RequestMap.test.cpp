
#include "../test-utils/test-utils.hpp"

static void test_req_line(RequestMap &reqMap)
{
    int fd;

    if ((fd = open((REQUESTS_PATH + std::string("get")).c_str(), O_RDONLY)) < 0)
        assert(0);

    Request req = test::simulateReq(reqMap, fd);
  
    assert(req.reqLine.method == "GET");
    assert(req.reqLine.uri == "/");
    assert(req.reqLine.version == "HTTP/1.1");

    test::display_success("Req line");
    test::closeFd(fd, reqMap);
}

static void test_headers(RequestMap &reqMap)
{
    int fd;

    if ((fd = open((REQUESTS_PATH + std::string("get")).c_str(), O_RDONLY)) < 0)
        assert(0);

   Request req = test::simulateReq(reqMap, fd);

    assert(req.headers["host"] == "localhost:8080");
    assert(req.headers["connection"] == "keep-alive");
    assert(req.headers["upgrade-insecure-requests"] == "1");
    assert(req.headers["accept"] == "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    assert(req.headers["user-agent"] == "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/604.5.6 (KHTML, like Gecko) Version/11.0.3 Safari/604.5.6");
    assert(req.headers["accept-language"] == "en-us");
    assert(req.headers["dnt"] == "1");
    assert(req.headers["accept-encoding"] == "gzip, deflate");

    assert(req.headers["headerQuiNexistePas"] == "");

    test::display_success("RequestMap headers");
    test::closeFd(fd, reqMap);
}

static void test_query_string(RequestMap &reqMap)
{
    int fd;

    if ((fd = open((REQUESTS_PATH + std::string("get")).c_str(), O_RDONLY)) < 0)
        assert(0);

   Request req = test::simulateReq(reqMap, fd);

    assert(req.reqLine.queryString == "a=b&cc=dd&eee=fff");

    test::display_success("Query string");
    test::closeFd(fd, reqMap);
}

static void test_empty_query_string(RequestMap &reqMap)
{
    try
    {
        int fd;

        if ((fd = open((REQUESTS_PATH + std::string("get_2")).c_str(), O_RDONLY)) < 0)
            assert(0);

       Request req = test::simulateReq(reqMap, fd);

        assert(req.reqLine.uri == "/");
        assert(req.reqLine.queryString == "");

        test::display_success("Empty query string");
        test::closeFd(fd, reqMap);
    }
    catch (const char *error)
    {
        std::cout << error << std::endl;
        assert(0);
    }
}

void test::test_request_map()
{
    ConfigParser parser(CONFIGS_PATH + std::string("one_server.conf"));
    ConfigParser::serverConfigs configs = parser.getServerConfigs();
    RequestMap reqMap(configs);
    
    test_req_line(reqMap);
    test_headers(reqMap);
    test_query_string(reqMap);
    test_empty_query_string(reqMap);
}

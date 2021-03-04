/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.test.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 14:26:19 by adrien            #+#    #+#             */
/*   Updated: 2020/10/19 16:54:28 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test-utils/test-utils.hpp"

static void test_location_inheritance()
{
    ConfigParser config(CONFIGS_PATH + std::string("loc_inheritance.conf"));

    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.size() == 1);

    assert(configs.front().autoIndex == true);
    assert(configs.front().root == "lolilol");
    assert(configs.front().addresses.front().host == "localhost");
    assert(configs.front().addresses.front().port == 80);
    assert(configs.front().locations.size() == 4);

    assert(configs.front().locations[0].uri == "/vasy/ok");
    assert(configs.front().locations[0].autoIndex == false);
    assert(configs.front().locations[0].root.value == "lolilol");

    assert(configs.front().locations[1].uri == "/encoreplus");
    assert(configs.front().locations[1].autoIndex == false);
    assert(configs.front().locations[1].root.value == "plus");

    assert(configs.front().locations[2].uri == "/test");
    assert(configs.front().locations[2].autoIndex == true);
    assert(configs.front().locations[2].root.value == "test123");

    assert(configs.front().locations[3].uri == "/ok");
    assert(configs.front().locations[3].autoIndex == true);
    assert(configs.front().locations[3].root.value == "lolilol");

    test::display_success("Location inheritance");
}

static void     test_default_server_values()
{
    ConfigParser config(CONFIGS_PATH + std::string("default_server_values.conf"));

    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.size() == 1);
    assert(configs.front().locations.empty());
    assert(configs.front().addresses.empty());
    assert(configs.front().root == DEFAULT_ROOT);
    assert(configs.front().clientMaxBodySizeInBytes == MAX_BODY_SIZE);
    assert(configs.front().autoIndex == false);
    assert(configs.front().serverNames.empty());
    assert(configs.front().indexes.empty());
    assert(configs.front().connect == true);

    test::display_success("Default server values");
}

static void     test_default_location_values()
{
    ConfigParser config(CONFIGS_PATH + std::string("default_location_values.conf"));

    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.size() == 1);
    assert(configs.front().locations.size() == 1);
    assert(configs.front().locations[0].autoIndex == false);
    assert(configs.front().locations[0].clientMaxBodySizeInBytes == MAX_BODY_SIZE);
    assert(configs.front().locations[0].root.value == DEFAULT_ROOT);
    assert(configs.front().locations[0].uri == "/");
    assert(configs.front().locations[0].methods.empty());
    assert(configs.front().locations[0].indexes.empty());

    test::display_success("Default location values");
}

static void     test_client_max_body_size()
{
    ConfigParser config(CONFIGS_PATH + std::string("client_max_body_size.conf"));

    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.size() == 2);

    assert(configs.front().clientMaxBodySizeInBytes == MAX_BODY_SIZE);
    assert(configs.front().locations.size() == 2);
    assert(configs.front().locations[0].clientMaxBodySizeInBytes == 10000);
    assert(configs.front().locations[1].clientMaxBodySizeInBytes == MAX_BODY_SIZE);

    assert(configs.back().clientMaxBodySizeInBytes == 10 * 1000 * 1000);
    assert(configs.back().locations.size() == 4);
    assert(configs.back().locations[0].clientMaxBodySizeInBytes == 1024);
    assert(configs.back().locations[1].clientMaxBodySizeInBytes == 10 * 1000 * 1000);
    assert(configs.back().locations[2].clientMaxBodySizeInBytes == 5000);
    assert(configs.back().locations[3].clientMaxBodySizeInBytes == 0);

    test::display_success("Client max body size");
}

static void test_accept_methods()
{
    ConfigParser config(CONFIGS_PATH + std::string("accept_methods.conf"));
    ConfigParser::serverConfigs configs = config.getServerConfigs();


    assert(configs.size() == 1);
    assert(configs.front().locations.size() == 4);

    assert(configs.front().locations[0].methods.size() == 1);
    assert(configs.front().locations[0].methods[0] == "GET");

    assert(configs.front().locations[1].methods[0] == "PUT");
    assert(configs.front().locations[1].methods[1] == "POST");

    assert(configs.front().locations[2].methods[0] == "HEAD");

    assert(configs.front().locations[3].methods.empty());

    test::display_success("Accept methods");
}

static void test_indexes()
{
    ConfigParser config(CONFIGS_PATH + std::string("indexes.conf"));

    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.size() == 1);

    assert(configs.front().indexes.size() == 3);
    assert(configs.front().indexes[0] == "index.html");
    assert(configs.front().indexes[1] == "index.php");
    assert(configs.front().indexes[2] == "index.oklm");

    assert(configs.front().locations.size() == 1);
    assert(configs.front().locations[0].indexes.size() == 1);
    assert(configs.front().locations[0].indexes[0] == "index.tktpas");

    test::display_success("Indexes");
}

static void     test_no_end_closure()
{
    try {
        ConfigParser config(CONFIGS_PATH + std::string("no_closure.conf"));

        assert(0);
    }
    catch (const std::string &ex)
    {
       assert(1);
    }

    try {
        ConfigParser config(CONFIGS_PATH + std::string("no_location_closure.conf"));

        assert(0);
    }
    catch (const std::string &ex)
    {
       assert(1);
    }

    test::display_success("Throw if no end closure");
}

static void     test_bad_client_max_size()
{
   try {
        ConfigParser config(CONFIGS_PATH + std::string("bad_max_size_char.conf"));

        assert(0);
    }
    catch (const std::string &ex)
    {
       assert(ex.find("Please specify a correct unit measurement") != std::string::npos);
    }

    test::display_success("Throw bad client_max_body_size");
}

static void     test_bad_path()
{
     try {
        ConfigParser config(CONFIGS_PATH + std::string("existepas"));

        assert(0);
    }
    catch (const std::string &ex)
    {
       assert(ex.find("Unable to open config file") != std::string::npos);
    }

    test::display_success("Throw if bad config path");
}

static void     test_empty_conf()
{
     try {
        ConfigParser config(CONFIGS_PATH + std::string("empty.conf"));

        assert(0);
    }
    catch (const std::string &ex)
    {
        assert(1);
    }

    test::display_success("Throw if empty config");
}

static void     test_bad_autoindex()
{
    try {
        ConfigParser config(CONFIGS_PATH + std::string("bad_autoindex.conf"));

        assert(0);
    }
    catch (const std::string &ex)
    {
       assert(ex.find("Expected on | off") != std::string::npos);
    }

    test::display_success("Throw if autoindex != on && autoindex != off");
}

static void     test_multiple_listens()
{
   ConfigParser config(CONFIGS_PATH + std::string("multiple_listen.conf"));

   ConfigParser::serverConfigs configs = config.getServerConfigs();

   assert(configs.front().addresses[0].host == "127.0.0.1");
   assert(configs.front().addresses[0].port == 8080);
   assert(configs.front().addresses[1].host == "127.0.0.1");
   assert(configs.front().addresses[1].port == 8081);
   assert(configs.front().addresses[2].host == "127.0.0.1");
   assert(configs.front().addresses[2].port == 8082);

   assert(configs.front().addresses[3].host == "1.2.3.4");
   assert(configs.front().addresses[3].port == 80);

    test::display_success("Multiple listen directive");
}

static void     test_error_pages()
{
   ConfigParser config(CONFIGS_PATH + std::string("error.conf"));

   ConfigParser::serverConfigs configs = config.getServerConfigs();

   assert(configs.front().errorPages.front().codes.at(0) == "500");
   assert(configs.front().errorPages.front().codes.at(1) == "501");
   assert(configs.front().errorPages.front().codes.at(2) == "502");

   assert(configs.front().errorPages.front().uri == "/error/50x.html");

   assert(configs.front().errorPages.back().codes.at(0) == "400");
   assert(configs.front().errorPages.back().codes.at(1) == "401");
   assert(configs.front().errorPages.back().codes.at(2) == "402");
   assert(configs.front().errorPages.back().codes.at(3) == "403");


   assert(configs.front().errorPages.back().uri == "/error/40x.html");


   assert(configs.front().locations[0].methods.empty());
   assert(configs.front().locations[0].indexes.empty());

   assert(configs.front().locations[0].errorPages.front().codes.at(0) == "400");
   assert(configs.front().locations[0].errorPages.front().codes.size() == 1);
   assert(configs.front().locations[0].errorPages.front().uri == "/error_test/400.html");

   assert(configs.front().locations[0].errorPages.size() == 3);

   test::display_success("Directive error_page");
}

static void test_cgi_extensions()
{
   ConfigParser config(CONFIGS_PATH + std::string("cgi_extensions.conf"));

   ConfigParser::serverConfigs configs = config.getServerConfigs();

   assert(configs.front().cgis.size() == 1);
   assert(configs.front().cgis.front().extension == ".php");
   assert(configs.front().cgis.front().executablePath == "/usr/bin/php-cgi");

   assert(configs.front().locations.front().cgis.size() == 1);
   assert(configs.front().locations.front().cgis.front().extension == ".php");
   assert(configs.front().locations.front().cgis.front().executablePath == "/usr/bin/php-cgi");

   assert(configs.front().locations.back().cgis.size() == 3);
   assert(configs.front().locations.back().cgis[0].extension == ".php");
   assert(configs.front().locations.back().cgis[1].extension == ".pl");
   assert(configs.front().locations.back().cgis[2].extension == ".py");

   assert(configs.front().locations.back().cgis[0].executablePath == "/usr/bin/php-cgi");
   assert(configs.front().locations.back().cgis[1].executablePath == "/usr/bin/pl-cgi");
   assert(configs.front().locations.back().cgis[2].executablePath == "/usr/bin/py-cgi");

   test::display_success("Correct values for cgi_extensions");
}

static void test_bad_cgi_extensions()
{
   try {
        ConfigParser config(CONFIGS_PATH + std::string("bad_cgi_extensions.conf"));

        assert(0);
   } catch (const std::string &ex) {
       assert(1);
   }

   test::display_success("Incorrect values for cgi_extensions");
}

static void test_auth_basic_default_values()
{
    ConfigParser config(CONFIGS_PATH + std::string("auth_basic_default.conf"));

    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.front().auth.isActive() == false);
    assert(configs.front().auth.realm == "Basic authentification");
    assert(configs.front().auth.ids.empty());

    assert(configs.front().locations.front().auth.isActive() == false);
    assert(configs.front().locations.front().auth.realm == "Basic authentification");
    assert(configs.front().auth.ids.empty());

   test::display_success("AuthBasic default values");
}

static void test_auth_basic_inheritance()
{
    ConfigParser config(CONFIGS_PATH + std::string("auth_basic_inheritance.conf"));

    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.front().auth.isActive());
    assert(configs.front().auth.realm == "\"realm\"");
    assert(configs.front().auth.ids.size() == 1);

    assert(configs.front().locations.front().auth.isActive());
    assert(configs.front().locations.front().auth.realm == "\"realm 2\"");
    assert(configs.front().locations.front().auth.ids.size() == 3);

    assert(configs.front().locations.back().auth.isActive() == false);
    assert(configs.front().locations.back().auth.realm == "\"realm\"");
    assert(configs.front().locations.back().auth.ids.size() == 1);

   test::display_success("AuthBasic inheritance");
}

static void test_auth_basic()
{
    ConfigParser config(CONFIGS_PATH + std::string("auth_basic.conf"));

    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.front().locations.front().auth.isActive());
    assert(configs.front().locations.front().auth.ids.size() == 2);
    assert(configs.front().locations.front().auth.realm == "\"realm\"");

   test::display_success("AuthBasic");
}

static void test_bad_auth_basic()
{
   try {
        ConfigParser config(CONFIGS_PATH + std::string("bad_auth_basic.conf"));

        assert(0);
   } catch (const std::string &ex) {
       assert(1);
   }

   test::display_success("AuthBasic incorrect values");
}

static void test_upload_store()
{
    ConfigParser config(CONFIGS_PATH + std::string("upload_store.conf"));


    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.front().uploadStore == "/etc");
    assert(configs.front().locations.front().uploadStore == "/etc/nginx");
    assert(configs.front().locations.back().uploadStore == "/etc");

    test::display_success("Upload store");
}

static void test_bad_upload_store()
{
   try {
        ConfigParser config(CONFIGS_PATH + std::string("bad_upload_store.conf"));

        assert(0);
   } catch (const std::string &ex) {
       assert(1);
   }

   test::display_success("Upload store incorrect path");
}

static void test_connect()
{
    ConfigParser config(CONFIGS_PATH + std::string("connect.conf"));


    ConfigParser::serverConfigs configs = config.getServerConfigs();

    assert(configs.front().connect == false);

    test::display_success("Connect");
}




void    test::test_config_parser()
{
    try
    {
        test_location_inheritance();
        test_default_server_values();
        test_default_location_values();
        test_client_max_body_size();
        test_accept_methods();
        test_indexes();
        test_no_end_closure();
        test_bad_client_max_size();
        test_bad_path();
        test_empty_conf();
        test_bad_autoindex();
        test_multiple_listens();
        test_error_pages();
        test_cgi_extensions();
        test_bad_cgi_extensions();
        test_auth_basic_default_values();
        test_auth_basic_inheritance();
        test_auth_basic();
        test_bad_auth_basic();
        test_upload_store();
        test_bad_upload_store();
        test_connect();
    }
    catch (const std::string &ex)
    {
        std::cout << ex << std::endl;
        assert(0);
    }
}




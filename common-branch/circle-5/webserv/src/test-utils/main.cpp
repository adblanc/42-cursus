/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 18:14:49 by adrien            #+#    #+#             */
/*   Updated: 2020/10/08 17:11:29 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test-utils.hpp"

int main()
{
    test::display("=== CONFIG PARSER ===", YELLOW);
    test::test_config_parser();

    test::display("=== REQUEST_MAP ===", YELLOW);
    test::test_request_map();

    test::display("=== REQUEST ===", YELLOW);
    test::test_request();

    test::display("=== Mime Types ===", YELLOW);
    test::test_mime_types();
    
    return (0);
}
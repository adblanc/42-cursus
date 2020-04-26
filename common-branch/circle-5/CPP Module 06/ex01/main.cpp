/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:19:08 by adrien            #+#    #+#             */
/*   Updated: 2020/03/09 13:06:27 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void *serialize(void)
{
    static const std::string alphaNum =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *res = new char[20];
    std::size_t length;

    length = alphaNum.size();
    for (int i = 0; i < 8; i++)
        res[i] = alphaNum[std::rand() % length];

    *(reinterpret_cast<int *>(&res[8])) = std::rand();

    for (int i = 12; i < 20; i++)
        res[i] = alphaNum[std::rand() % length];

    return (reinterpret_cast<void *>(res));
}

Data *deserialize(void *raw)
{
    Data *data = new Data;
    int i;
    char *value = reinterpret_cast<char *>(raw);

    i = 0;
    while (i < 8)
    {
        data->s1 += value[i];
        i++;
    }
    data->n = *(reinterpret_cast<int *>(&value[i]));
    i += 4;
    while (i < 20)
    {
        data->s2 += value[i];
        i++;
    }
    return (data);
}

int main()
{
    void *dataSerialized;
    Data *data;

    srand(time(NULL));

    dataSerialized = serialize();
    data = deserialize(dataSerialized);

    std::cout << "Data serialized :" << std::endl;

    std::cout << dataSerialized << std::endl
              << std::endl;

    std::cout << "Data deserialized :" << std::endl;
    std::cout << data->s1 << std::endl;
    std::cout << data->n << std::endl;
    std::cout << data->s2 << std::endl;

    delete reinterpret_cast<char *>(dataSerialized);
    delete data;
    return (0);
}

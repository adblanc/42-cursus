/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConvertScalar.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 09:14:50 by adrien            #+#    #+#             */
/*   Updated: 2020/03/09 15:08:47 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConvertScalar.hpp"

ConvertScalar::ConvertScalar(void)
{
    this->input = "0";
    this->precision = 1;
    this->setType();
};

ConvertScalar::ConvertScalar(std::string const &input)
{
    this->input = input;
    this->setPrecision(input.c_str());
    this->setType();
};

bool ConvertScalar::isFloat()
{
    return (this->input.length() > 1 && this->input[this->input.length() - 1] == 'f' && this->input != "-inf" && this->input != "+inf");
}
bool ConvertScalar::isDouble()
{
    bool hasDot = false;

    for (size_t i = 0; i < this->input.length(); i++)
        if (this->input[i] == '.')
            hasDot = true;
    return (hasDot || this->input == "-inf" || this->input == "+inf" || this->input == "nan");
}

bool ConvertScalar::isChar()
{
    return (this->input.length() == 3 && this->input[0] == '\'' && this->input[2] == '\'');
}

void ConvertScalar::setType(void)
{
    double value;
    char *ptr;
    const char *input_str;

    input_str = this->input.c_str();

    value = strtod(input_str, &ptr);
    if (this->isFloat())
    {
        if (ptr != &input_str[this->input.length() - 1])
            throw ConvertScalar::Impossible();
        this->type = "float";
        this->inputFloat = static_cast<float>(value);
    }
    else if (this->isDouble())
    {
        if (ptr != &input_str[this->input.length()] && this->input != "+inf" && this->input != "-inf" && this->input != "nan")
            throw ConvertScalar::Impossible();
        this->type = "double";
        this->inputDouble = static_cast<double>(value);
    }
    else if (this->isChar())
    {
        this->type = "char";
        this->inputChar = this->input[1];
    }
    else
    {
        if (ptr != &input_str[this->input.length()])
            throw ConvertScalar::Impossible();
        this->type = "int";
        this->inputDouble = static_cast<double>(value);
    }
};

double ConvertScalar::getInput(void)
{
    if (this->type == "float")
        return this->inputFloat;
    if (this->type == "char")
        return this->inputChar;

    return this->inputDouble;
}

ConvertScalar::ConvertScalar(const ConvertScalar &src)
{
    *this = src;
};

ConvertScalar::~ConvertScalar(){

};

ConvertScalar &ConvertScalar::operator=(const ConvertScalar &rhs)
{
    if (this != &rhs)
    {
        this->precision = rhs.precision;
    }
    return (*this);
};

ConvertScalar::NonDisplayable::NonDisplayable(void){

};

ConvertScalar::NonDisplayable::NonDisplayable(const ConvertScalar::NonDisplayable &src)
{
    *this = src;
};

ConvertScalar::NonDisplayable::~NonDisplayable() throw(){

};

ConvertScalar::NonDisplayable &ConvertScalar::NonDisplayable::operator=(const ConvertScalar::NonDisplayable &rhs)
{
    static_cast<void>(rhs);
    return (*this);
};
const char *ConvertScalar::NonDisplayable::what(void) const throw()
{
    return "Non displayable";
}

ConvertScalar::Impossible::Impossible(void){

};

ConvertScalar::Impossible::Impossible(const ConvertScalar::Impossible &src)
{
    *this = src;
};

ConvertScalar::Impossible::~Impossible() throw(){

};

ConvertScalar::Impossible &ConvertScalar::Impossible::operator=(const ConvertScalar::Impossible &rhs)
{
    static_cast<void>(rhs);
    return (*this);
};
const char *ConvertScalar::Impossible::what(void) const throw()
{
    return "impossible";
}

char ConvertScalar::toChar()
{
    char c;
    double n = this->getInput();

    if (std::isnan(n))
        throw ConvertScalar::Impossible();

    c = static_cast<char>(n);

    if (!std::isprint(c) || n < 0 || n > 255)
        throw ConvertScalar::NonDisplayable();

    return (c);
}

int ConvertScalar::toInt()
{
    bool outRange;
    double n = this->getInput();

    outRange = (n < static_cast<double>(INT_MIN) || n > static_cast<double>(INT_MAX));
    if (std::isnan(n) || std::isinf(n) || outRange)
        throw ConvertScalar::Impossible();

    return (static_cast<int>(n));
}

float ConvertScalar::toFloat()
{
    double n = this->getInput();
    return (static_cast<float>(n));
}

double ConvertScalar::toDouble()
{
    double n = this->getInput();
    return (static_cast<double>(n));
}

void ConvertScalar::displayChar()
{
    std::cout << "char: ";
    try
    {
        char c;

        c = this->toChar();
        std::cout << "'" << c << "'" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ConvertScalar::displayInt()
{
    std::cout << "int: ";
    try
    {
        int i;

        i = this->toInt();
        std::cout << i << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ConvertScalar::displayFloat()
{
    std::cout << "float: ";
    try
    {
        float f;

        f = this->toFloat();
        std::cout << std::fixed << std::setprecision(this->precision) << f << "f" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ConvertScalar::displayDouble()
{
    std::cout << "double: ";
    try
    {
        double d;

        d = this->toDouble();
        std::cout << std::fixed << std::setprecision(this->precision) << d << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ConvertScalar::setPrecision(char const *s)
{
    int i;
    int precision;
    bool countPrecision;

    countPrecision = false;
    precision = 0;
    i = 0;
    while (s[i] && (std::isdigit(s[i]) || s[i] == '.' || s[i] == '-'))
    {
        if (countPrecision)
            precision++;
        if (s[i] == '.')
        {
            if (countPrecision)
                break;
            countPrecision = true;
        }
        i++;
    }
    if (!precision)
        precision = 1;
    this->precision = precision;
}

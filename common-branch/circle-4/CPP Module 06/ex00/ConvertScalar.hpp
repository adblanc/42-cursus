/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConvertScalar.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 09:14:33 by adrien            #+#    #+#             */
/*   Updated: 2020/03/09 14:54:42 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTSCALAR_HPP
#define CONVERTSCALAR_HPP

#include <stdexcept>
#include <cmath>
#include <climits>
#include <iostream>
#include <cctype>
#include <string>
#include <iomanip>

class ConvertScalar
{
public:
    ConvertScalar(void);
    ConvertScalar(std::string const &input);
    ConvertScalar(const ConvertScalar &src);
    ~ConvertScalar();

    ConvertScalar &operator=(const ConvertScalar &rhs);

    class NonDisplayable : public std::exception
    {
    public:
        NonDisplayable(void);
        NonDisplayable(const NonDisplayable &src);
        virtual ~NonDisplayable() throw();

        NonDisplayable &operator=(const NonDisplayable &rhs);

        virtual const char *what(void) const throw();
    };

    class Impossible : public std::exception
    {
    public:
        Impossible(void);
        Impossible(const Impossible &src);
        virtual ~Impossible() throw();

        Impossible &operator=(const Impossible &rhs);

        virtual const char *what(void) const throw();
    };

    void displayChar();
    void displayInt();
    void displayFloat();
    void displayDouble();

    double getInput();

    void setPrecision(char const *s);

private:
    std::string input;
    std::string type;
    int precision;

    char inputChar;
    float inputFloat;
    double inputDouble;

    bool isFloat();
    bool isDouble();
    bool isChar();

    char toChar();
    int toInt();
    float toFloat();
    double toDouble();

    void setType();
};

#endif

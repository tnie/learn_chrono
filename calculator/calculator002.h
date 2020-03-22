#pragma once

#include <iostream>
#include <cassert>

class Token
{
public:
    char kind;
    double value;
};

class Token_stream;

double expression()
{

}

double term()
{
    char op;
    std::cin >> op;
    switch (op)
    {
    case '*':
        primary();
        break;
    case '/':
        primary();
        break;
    case '%':
        primary();
        break;
    default:
        break;
    }
}

double primary()
{
    char op;
    double val;
    std::cin >> op;
    if (op == '(')
    {
        val = expression();
        std::cin >> op;
        assert(op == ')');
    }
    else
    {
        val = number();
    }
    return val;
}

double number()
{
    double val;
    std::cin >> val;
    return val;
}
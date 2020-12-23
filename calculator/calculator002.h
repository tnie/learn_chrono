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

double expression();

double number()
{
    double val;
    std::cin >> val;
    return val;
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
        std::cin.putback(op);
        val = number();
    }
    return val;
}

double term()
{
    double lhs = primary();
    while (true)
    {
        char op;
        std::cin >> op;
        switch (op)
        {
        case '*':
            lhs *= primary();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)
            {
                throw DivideZero();
            }
            lhs /= d;
            break;
        }        
        case '%':
            //lhs %= primary();
            break;
        default:
            std::cin.putback(op);
            return lhs;
        }
    }
}

double expression()
{
    double lhs = term();
    while (true)
    {
        char op;
        std::cin >> op;
        switch (op)
        {
        case '+':
            lhs += term();
            break;
        case '-':
            lhs -= term();
            break;
        default:
            std::cin.putback(op);
            return lhs;
        }
    }
}

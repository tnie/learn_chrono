#pragma once

#include <iostream>
#include <spdlog/spdlog.h>
#include <string>
#include <sstream>
#include "common.h"

namespace c1
{
    double calculator(const std::string& statement)
    {
        std::istringstream iss(statement);
        double x, y, result = 0;
        char op;
        std::istream& alias = statement.empty() ? std::cin : iss;
        alias >> x >> op >> y;
        if (!alias)
        {
            throw BadInput();
        }
        switch (op)
        {
        case '+':
            result = x + y;
            break;
        case '-':
            result = x - y;
            break;
        case '*':
            result = x * y;
            break;
        case '/':
            if (y == 0)
            {
                throw DivideZero();
            }
            result = x / y;
            break;
        case '%':
            result = static_cast<int>(x) % static_cast<int>(y);
        default:
            throw Todo();
            break;
        }
        if (statement.empty())
        {
            spdlog::info("{} {} {}={}", x , op, y, result);
        }
        else
        {
            spdlog::info("{}={}", statement, result);
        }
        return result;
    }
}

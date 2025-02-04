#pragma once
#include <string>
#include <sstream>

struct Position{
    double t, x, y, z;

    static Position ParseLine(std::string line);
};
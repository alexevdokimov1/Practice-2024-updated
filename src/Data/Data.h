#pragma once
#include <string>
#include <sstream>

struct Position{
    double t, x, y, z;

    static Position parseLine(std::string line);
};
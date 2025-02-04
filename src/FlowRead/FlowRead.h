#pragma once
#include <vector>
#include <string>
#include <fstream>

struct Position{
    double t, x, y, z;
};

class FlowRead {
    private:
        std::ifstream file;
    public:
        FlowRead(std::string filename);
        bool next(std::vector<Position>& positions, int n=1);
        void reset();
        void skipLine();

};

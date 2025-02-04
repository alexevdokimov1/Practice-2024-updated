#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "../Data/Data.h"

class FlowRead {
    private:
        std::ifstream file;
    public:
        FlowRead(std::string filename);
        bool next(std::vector<Position>& positions, int n=1);
        void reset();
        void skipLine();
};

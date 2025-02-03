#include <vector>
#include <string>
#include <fstream>
#include <format>
#include <stdexcept>
#include "FileOperations.h"

void RetrieveData(std::vector<std::vector<double>>& values, int& line_count, std::string filename)
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("File " + filename +" doesn't exist");
    line_count = 0;
    std::string line;
    while (std::getline(file, line)) {
        line_count++;
    }
    file.clear();
    file.seekg(0, std::ios::beg);
    values.resize(4);
    for (int i = 0; i < 4; i++)

        values[i].resize(line_count);

    for (int j = 0; j < line_count; j++)
        for (int i = 0; i < 4; i++)
            file >> values[i][j];

    file.close();
    return;
}
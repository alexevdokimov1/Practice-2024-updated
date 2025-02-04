#include "Data.h"

Position Position::ParseLine(std::string line){
    std::stringstream ss(line);
    double t, x, y, z;
    ss >> t >> x >> y >> z;
    return {t, x, y, z};
}
#include "FlowRead.h"
#include <iostream>
#include <sstream>

FlowRead::FlowRead(std::string filename){
    file.open(filename);
    if(!file.is_open()){
           throw std::runtime_error("Failed to open file: " + filename);
    }
};

bool FlowRead::next(std::vector<Position>& positions, int n){

    positions.clear();
    std::streampos current_pos = file.tellg(); //get the current position of the file
    std::string line;
    double t, x, y, z;
    for(int i = 0; i < n; i++){
        if(std::getline(file, line)){
            std::istringstream iss(line);
            iss >> t >> x >> y >> z;
            positions.push_back({t, x, y, z});
        }
        else{
            file.seekg(current_pos);
            positions.clear();
            return false;


        }
    }
    file.seekg(current_pos);
    return true;
}


void FlowRead::reset(){
    file.seekg(0, std::ios::beg); //reset the file to the beginning
}

void FlowRead::skipLine(){
    std::string line;
    std::getline(file, line);
}

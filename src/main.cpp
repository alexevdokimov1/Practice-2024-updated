#include <iostream>
#include <vector>
#include <exception> 
#include <cmath>
#include <fstream> 
#include "Function/Function.h"
#include "Approximation/Approximation.h"
#include "FlowRead/FlowRead.h"
#include "Data/Data.h"

#define eps 0.0001

int main() {

    try {
    
    FlowRead realValueStream("../data/Real.txt");
    FlowRead calculatedValueStream("../data/Calculated.txt");

    std::vector<double> time_slice, x_slice, y_slice, z_slice;
    double x_closest, y_closest, z_closest;
    std::vector<double> x_sol, y_sol, z_sol;
    double x_del, y_del, z_del;

    std::ofstream output("../build/Result.txt");
    if (!output) {
        std::cout << "Output file can not be created\n";
        return 0;
    }
    
    std::vector<Position> real_positions;
    while(realValueStream.next(real_positions)){
        std::vector<Position> calculated_positions;
        while(calculatedValueStream.next(calculated_positions, 4)){
            if (real_positions[0].t > calculated_positions[1].t && real_positions[0].t < calculated_positions[2].t) {
                time_slice.clear();
                x_slice.clear();
                y_slice.clear();
                z_slice.clear();

                for(const auto& pos : calculated_positions) {
                    time_slice.push_back(pos.t);
                    x_slice.push_back(pos.x);
                    y_slice.push_back(pos.y);
                    z_slice.push_back(pos.z);
                }
                
                x_sol = Approximate(time_slice, x_slice, 3); //approximation of x to time
                y_sol = Approximate(x_slice, y_slice, 3); //approximation of y to x
                z_sol = Approximate(x_slice, z_slice, 3); //approximation of z to x
               

                x_closest =  calcEquation(x_sol[0], x_sol[1], x_sol[2], real_positions[0].x, real_positions[0].y, 
                    calculated_positions[1].x, calculated_positions[2].x, eps); //finding x closest


                y_closest = 0; //finding y based on y closest
                for (int v = 0; v < y_sol.size(); v++)
                    y_closest += y_sol[v] * pow(x_closest, 2 - v);

                z_closest = 0; //finding z based on z closest
                for (int v = 0; v < z_sol.size(); v++)
                    z_closest += z_sol[v] * pow(x_closest, 2 - v);

                x_del = std::abs(x_closest - real_positions[0].x);
                y_del = std::abs(y_closest - real_positions[0].y);
                z_del = std::abs(z_closest - real_positions[0].z);

                output << real_positions[0].t << "\t" << x_del << "\t" << y_del << "\t" << z_del << "\n";
                break;

            }
            else calculatedValueStream.skipLine();
        }
        realValueStream.skipLine();
    }

    output.close();

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception:\t" << e.what() << '\n';
        return 0;
    }
    return 0;
}
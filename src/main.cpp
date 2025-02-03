#include <iostream>
#include <vector>
#include <exception> 
#include <cmath>
#include <fstream> 
#include "Function/Function.h"
#include "Approximation/Approximation.h"
#include "FileOperations/FileOperations.h"

int main() {
    
    std::vector<std::vector<double>> experimental_values, calculated_values;
    int experimental_values_count, calculated_values_count;

    try {
        RetrieveData(experimental_values, experimental_values_count, "../data/Real.txt");
        RetrieveData(calculated_values, calculated_values_count, "../data/Calculated.txt");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception:\t" << e.what() << '\n';
        return 0;
    }

    std::vector<double> time_slice, x_slice, y_slice, z_slice;
    double x_closest, y_closest, z_closest;
    std::vector<double> x_sol, y_sol, z_sol;
    double x_del, y_del, z_del;

    std::ofstream output("../data/Result.txt");
    if (!output) {
        std::cout << "Output file can not be created\n";
        return 0;
    }

    int i_start = 0;
    for (int k = 0; k < experimental_values_count; k++) { //except first and last to set interval
        for (int i = i_start; i < calculated_values_count - 3; i++) {

            if (calculated_values[0][i+1] < experimental_values[0][k] && experimental_values[0][k] < calculated_values[0][i + 2]) { //if time is in interval

                time_slice = std::vector<double>(calculated_values[0].begin() + i, calculated_values[0].begin() + i + 4); //time slice
                x_slice = std::vector<double>(calculated_values[1].begin() + i, calculated_values[1].begin() + i + 4); //x slice
                y_slice = std::vector<double>(calculated_values[2].begin() + i, calculated_values[2].begin() + i + 4); //y slice
                z_slice = std::vector<double>(calculated_values[3].begin() + i, calculated_values[3].begin() + i + 4); //z slice
                
                x_sol = Approximate(time_slice, x_slice, 3); //approximation of x to time
                y_sol = Approximate(x_slice, y_slice, 3); //approximation of y to x
                z_sol = Approximate(x_slice, z_slice, 3); //approximation of z to x
               

                x_closest =  calcEquation(x_sol[0], x_sol[1], x_sol[2], experimental_values[0][k], experimental_values[1][k], 
                    calculated_values[1][i+1], calculated_values[1][i + 2], 0.001); //finding x closest
               
                y_closest = 0; //finding y based on y closest
                for (int v = 0; v < y_sol.size(); v++)
                    y_closest += y_sol[v] * pow(x_closest, 2 - v);

                z_closest = 0; //finding z based on z closest
                for (int v = 0; v < z_sol.size(); v++)
                    z_closest += z_sol[v] * pow(x_closest, 2 - v);

                x_del = std::abs(x_closest - experimental_values[1][k]);
                y_del = std::abs(y_closest - experimental_values[2][k]);
                z_del = std::abs(z_closest - experimental_values[3][k]);

                output << experimental_values[0][k] << "\t" << x_del << "\t" << y_del << "\t" << z_del << "\n";

                if(i>4)i_start = i - 4;

                break;
            }      
        }
    }

    output.close();

    return 0;
}
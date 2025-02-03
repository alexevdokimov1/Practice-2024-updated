#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Approximation.h"
#include "../Gaus/Gaus.h"

std::vector <double> Approximate(const std::vector<double>& x, const std::vector<double>& y, const int order) {

    std::vector<double> x_coefficients(2 * order - 1, 0);
    std::vector<double> y_coefficients(order, 0);

    for (int k = 0; k < 2 * order - 1; k++)
        for (int i = 0; i < x.size(); i++)
            x_coefficients[k] += std::pow(x[i], k);

    for (int k = 0; k < order; k++)
        for (int i = 0; i < x.size(); i++)
            y_coefficients[k] += y[i] * std::pow(x[i], k);

    std::vector<std::vector<double>> matrix(order, std::vector<double>(order));

    for (int k = 1; k < 2 * order; k++)
        for (int i = 0; i < k; i++)
            if (i < order && k - i - 1 < order)
                matrix[i][k - i - 1] = x_coefficients[k - 1];

    std::vector<double> x_sol = Gaus(matrix, y_coefficients, order);


    std::reverse(x_sol.begin(), x_sol.end());
    return x_sol;
}
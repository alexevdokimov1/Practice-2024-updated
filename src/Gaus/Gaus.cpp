#include <vector>
#include <cmath>
#include "Gaus.h"

void SwapToMax(std::vector<std::vector<double>>& matrix, std::vector<double>& b, int k, const int& n)
{
    int max_index = k;
    for (int i = k + 1; i < n; i++)
        if (std::abs(matrix[i][k]) > std::abs(matrix[max_index][k])) max_index = i;

    std::swap(matrix[k], matrix[max_index]);
    std::swap(b[k], b[max_index]);
}

std::vector<double> Gaus(std::vector<std::vector<double>> matrix, std::vector<double> b, const int n)
{
    double a_first;
    for (int k = 0; k < n; k++)
    {
        SwapToMax(matrix, b, k, n);

        b[k] /= matrix[k][k];
        for (int i = n - 1; i >= 0; i--)
            matrix[k][i] /= matrix[k][k];

        for (int i = k + 1; i < n; i++) {
            a_first = matrix[i][k];
            b[i] = b[i] - b[k] * a_first;
            for (int j = k; j < n; j++)
                matrix[i][j] = matrix[i][j] - matrix[k][j] * a_first;
        }
    }
    std::vector<double> x(n);
    x[n - 1] = b[n - 1] / matrix[n - 1][n - 1];

    double s;

    for (int i = n - 2; i >= 0; i--)
    {
        s = 0;
        for (int j = i + 1; j < n; j++)
            s += matrix[i][j] * x[j];
        x[i] = b[i] - s;
    }
    return x;
}
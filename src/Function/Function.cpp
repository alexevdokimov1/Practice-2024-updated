#include <map>
#include <vector>
#include <cmath>
#include "Function.h"

double f(Equation& values, double x) {
    return (2 * values.a * x + values.b) * (values.a * x * x + values.b * x + values.c - values.y0) + x - values.x0;
}

double calcEquation(double a, double b, double c, double x0_param, double y0_param, double left, double right, double eps)
{
    Equation values{a, b, c, x0_param, y0_param};

    if (std::abs(f(values, left)) < eps) return left;
    if (std::abs(f(values, right)) < eps) return right;
    while (std::abs(right - left) > 2 * eps) {
        double c = (left + right) / 2;
        if (std::abs(f(values, c)) < eps) return c;
        else if (f(values, left) * f(values, c) < 0) right = c;
        else left = c;
    }
    return (left + right) / 2;
}
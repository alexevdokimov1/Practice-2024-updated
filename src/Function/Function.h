#pragma once
struct Equation {
    double a;
    double b;
    double c;
    double x0;
    double y0;
};
double calcEquation(double a, double b, double c, double x0, double y0, double x_min, double x_max, double eps);
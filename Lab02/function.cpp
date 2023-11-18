#include <iostream>
#include <cmath>
#include "func.h"

using namespace std;

// Function representing the given equation
double f(double x) {
    return pow(x, 3.0) - 3 * pow(x, 2.0) + 9 * x - 8;
}

// First derivative of the function f(x)
double f_(double x) {
    return 3 * pow(x, 2.0) - 6 * x + 9;
}

// Second derivative of the function f(x)
double f__(double x) {
    return 6 * x - 6;
}

// Function for the iteration in the Iterations method
double ff(double x) {
    return pow(3 * pow(x, 2.0) - 9 * x + 8, 1.0 / 3);
}

// Newton's method to find the root of the equation
double newton(double a, double b, double eps) {
    unsigned short count = 0;
    double x = 0;

    if ((f(a) * f(b)) > 0) {
        cout << "Error: The initial values do not bracket the root." << endl;
        exit(-1);
    }

    if ((f(a) * f__(a)) < 0) {
        swap(a, b);
    }

    do {
        x = a - f(a) / f_(a);
        ++count;
        cout << "Newton's Method - Iteration " << count << ": Root = " << x << endl;

        if (abs(x - a) < eps) {
            break;
        }

        a = x;
    } while (true);

    cout << endl;
    return a;
}

// Iterations method to find the root of the equation
double iterations(double a, double b, double eps) {
    if ((f(a) * f(b)) > 0) {
        cout << "Error: The initial values do not bracket the root." << endl;
        exit(-1);
    }

    double x0 = a, x1 = b;
    unsigned short count = 0;

    do {
        x1 = ff(x0);
        ++count;
        cout << "Iterations Method - Iteration " << count << ": Root = " << x1 << endl;

        if (fabs(x1 - x0) < eps) {
            break;
        }

        x0 = x1;
    } while (true);

    cout << endl;
    return x1;
}

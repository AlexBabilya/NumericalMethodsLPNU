#include <iostream>
#include <cmath>
#include "func.h"

using namespace std;

int main() {
    double a = 1, b = 2, eps = 0.00001;

    cout << "This program is created to solve nonlinear equations using Newton and Iterations methods." << endl
         << "For example, we will be using the equation x^3-3x^2+9x-8." << endl
         << "Accuracy is 0.00001 and limits [1;2]." << endl << endl;

    cout << "Root by Newton = " << newton(a, b, eps) << endl << endl;
    cout << "Root by Iterations = " << iterations(a, b, eps) << endl << endl;

    cout << "Enter your limits and accuracy (f(a)*f(b) must be negative and |a - b| must be > Accuracy):" << endl
         << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "Accuracy: ";
    cin >> eps;

    cout << "Root by Newton = " << newton(a, b, eps) << endl << endl;
    cout << "Root by Iterations = " << iterations(a, b, eps) << endl << endl;

    return 0;
}


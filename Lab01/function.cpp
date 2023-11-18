#include <iostream>
#include <cmath>
#include "func.h"

using namespace std;

double f(double x) {
    return pow(x, 3.0) - 3 * pow(x, 2.0) + 9 * x - 8;
}

double f_(double x) {
    return 3 * pow(x, 2.0) + 6 * x + 9;
}

double dixit(double a, double b, double eps) {
    unsigned short count = 0;
    double c;

    if ((f(a) * f(b)) > 0) {
        cout << "Error: f(a) * f(b) must be negative" << endl;
        return -1;
    }

    do {
        c = (a + b) / 2;

        if (f(a) * f(c) < 0) {
            b = c;
        } else if (f(b) * f(c) < 0) {
            a = c;
        } else {
            cout << "The root is not found" << endl;
            return 0;
        }

        count++;
    } while (fabs(b - a) > eps);

    cout << "Number of iterations for dixit is " << count << endl << endl;
    return c;
}

double chords(double a, double b, double eps) {
    unsigned short count = 0;
    double x;

    if ((f(a) * f(b)) > 0) {
        cout << "Error: f(a) * f(b) must be negative" << endl;
        return -1;
    }

    do {
        if (fabs(b - a) < eps) {
            return (a + b) / 2;
        }

        if ((f(b) - f(a)) == 0) {
            cout << "Error: Division by zero" << endl;
            return -1;
        }

        x = a - ((f(a) * (b - a)) / (f(b) - f(a)));

        ++count;

        if (fabs(x - a) < eps) {
            break;
        }

        a = x;
    } while (true);

    cout << "Number of iterations for chords is " << count << endl << endl;
    return a;
}

int main() {
    double a = 1, b = 2, eps = 0.00001;

    cout << "This program is created to solve nonlinear equations using chords and dixit methods." << endl << endl
         << "For example, we will be using such equations as x^3 - 3x^2 + 9x - 8." << endl
         << "Accuracy is 0.00001 and limits [1; 2]." << endl << endl;

    cout << "Root by dixit = " << dixit(a, b, eps) << endl << endl;
    cout << "Root by chords = " << chords(a, b, eps) << endl << endl;

    cout << "Enter your limits and accuracy (f(a) * f(b) must be negative and |a - b| must be > Accuracy):" << endl
         << "a: ";
    cin >> a;

    cout << "b: ";
    cin >> b;

    cout << "Accuracy: ";
    cin >> eps;

    cout << "Root by dixit = " << dixit(a, b, eps) << endl << endl;
    cout << "Root by chords = " << chords(a, b, eps) << endl << endl;

    return 0;
}


#include <iostream>
#include <cmath>

using namespace std;

double fi1(double x) {
    return sin(x + 1) - 1.2;
}

double fi2(double y) {
    return (2 - cos(y)) / 2;
}

double Det(double a[2][2]) {
    return a[0][0] * a[1][1] - (a[0][1] * a[1][0]);
}

double Jcobi(double x, double y) {
    double mas[2][2];
    mas[0][0] = 2;
    mas[0][1] = -sin(y);
    mas[1][0] = cos(y);
    mas[1][1] = -1;
    return Det(mas);
}

double deltaX(double x, double y) {
    double mas[2][2];
    mas[0][0] = 2 * x + cos(y) - 2;
    mas[0][1] = -sin(y);
    mas[1][0] = sin(x + 1) - y - 1.2;
    mas[1][1] = -1;
    return Det(mas);
}

double deltaY(double x, double y) {
    double mas[2][2];
    mas[0][0] = 2;
    mas[0][1] = 2 * x + cos(y) - 2;
    mas[1][0] = cos(y);
    mas[1][1] = sin(x + 1) - y - 1.2;
    return Det(mas);
}

void NewtonMethod(double ep) {
    double x0 = 0.5;
    double y0 = -0.2;

    if (Jcobi(x0, y0) == 0) {
        cout << "Error" << endl;
        return;
    } else {
        cout << "Newton Method" << endl << endl;
        double x1 = x0 - (deltaX(x0, y0) / Jcobi(x0, y0));
        double y1 = y0 - (deltaY(x0, y0) / Jcobi(x0, y0));
        int k = 0;
        cout << "| " << k << " | \tx = " << x0 << "\t| \ty = " << y0 << "\t| \teps = " << ep << endl;
        do {
            x0 = x1;
            y0 = y1;
            x1 = x0 - (deltaX(x0, y0) / Jcobi(x0, y0));
            y1 = y0 - (deltaY(x0, y0) / Jcobi(x0, y0));
            k++;
            cout << "| " << k << " | \tx = " << x1 << "\t| \ty = " << y1 << "\t| \teps = " << ep << endl;
        } while ((fabs(x1 - x0) + fabs(y1 - y0)) > ep);
    }
}

bool check(double x, double y) {
    return fabs(sin(x + 1) - 1.2) < 1 && fabs((2 - cos(y)) / 2) < 1;
}

void IterationMethod(double eps) {
    double xprev = 0.5;
    double yprev = -0.2;
    cout << "Iteration Method" << endl << endl;
    if (!check(xprev, yprev)) {
        cout << "Error" << endl;
        return;
    } else {
        double x = xprev, y = yprev;
        int k = 0;
        cout << "| " << k << " | \tx = " << x << "\t| \ty = " << y << "\t| \teps = " << eps << endl;
        do {
            xprev = x;
            yprev = y;
            x = fi2(yprev);
            y = fi1(xprev);
            k++;
            cout << "| " << k << " | \tx = " << x << "\t| \ty = " << y << "\t| \teps = " << eps << endl;
        } while ((fabs(x - xprev) + fabs(y - yprev)) > eps);
    }
    cout << endl;
}

int main() {
    double eps = 0.001;
    IterationMethod(eps);
    NewtonMethod(eps);
    return 0;
}


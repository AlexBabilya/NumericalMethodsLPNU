#include <cmath>
#include <iostream>
#include <stdio.h>

using namespace std;

bool is(double X[10]) {
    // Implement the logic for checking if the values in X are valid.
    // Return true if valid, false otherwise.
    return true; // Placeholder, replace with actual logic.
}

void methodLagrange(double x0, double X[10], double Y[10]) {
    if (x0 == 0)
        return;
    if (is(X) == false) {
        return;
    }
    printf("\nLagrange method:\n");
    double Q, deltaY[9][9], H = X[1] - X[0];
    for (int i = 0; i < 9; i++)
        for (int k = 0; k < 9; k++)
            if (k != 0)
                deltaY[i][k] = 0;
            else
                deltaY[i][0] = Y[i + 1] - Y[i];
    for (int i = 1; i < 9; i++)
        for (int k = 0; k < 9 - i; k++)
            deltaY[k][i] = deltaY[k + 1][i - 1] - deltaY[k][i - 1];
    for (int i = 0; i < 10; i++) {
        double d = 1;
        for (int j = 0; j < 10; j++) {
            if (i == j) {
                printf("%+2.3lf ", x0 - X[j]);
                d = d * (x0 - X[j]);
            } else {
                printf("%+2.3lf ", X[i] - X[j]);
                d = d * (X[i] - X[j]);
            }
        }
        cout << d;
        printf("\t%5.2lf \n", Y[i]);
    }
    double QRes = 1, factorial = 1, res = Y[0];
    Q = (x0 - X[0]) / H;
    for (int i = 0; i < 9; i++) {
        factorial *= i + 1;
        QRes *= (Q - i);
        res += (QRes * deltaY[0][i]) / factorial;
    }
    printf("\ny = %f\n", res);
}

double newtone(const double x, const double h, const double* y, const int n, const double z) {
    double** dy = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; ++i)
        dy[i] = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; ++i)
        dy[0][i] = y[i];

    for (int i = 1; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (j > (n - i - 1))
                dy[i][j] = 0;
            else
                dy[i][j] = dy[i - 1][j + 1] - dy[i - 1][j];

    printf(" x      y");
    for (int i = 1; i < n; ++i)
        printf("     D%d y", i);
    puts("\n");

    for (int i = 0; i < n; ++i) {
        printf("%5.3lf", x + i * h);
        for (int j = 0; j < n; ++j)
            if (dy[j][i] == 0)
                break;
            else
                printf("%10.6lf", dy[j][i]);
        puts("");
    }

    double ser = 0;
    for (int i = 0; i < n; ++i)
        ser += (x + i * h);
    ser /= n;

    long long f = 1;
    double q, k, res = 0;
    if (z < ser) {
        q = (z - x) / h;
        for (int i = 0; i < n; ++i) {
            if (i != 0)
                f *= i;
            if (i == 0)
                k = 1;
            else if (i == 1)
                k = q;
            else
                k *= q - i + 1;
            res += (dy[i][0] * k) / f;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            q = (z - (x + (n - 1) * h)) / h;
            if (i != 0)
                f *= i;
            if (i == 0)
                k = 1;
            else if (i == 1)
                k = q;
            else
                k *= q + i - 1;
            res += (dy[i][n - i - 1] * k) / f;
        }
    }

    for (int i = 0; i < n; ++i)
        free(dy[i]);
    free(dy);

    return res;
}

int main() {
    double X[6] = {0.59, 0.7, 0.81, 0.9, 0.95, 1};
    double Y[6] = {2.94, 3.2, 3.38, 3.53, 3.75, 4.06};

    // Output the given data
    cout << " x = 0.59, 0.7, 0.81, 0.9, 0.95, 1" << endl;
    cout << " y = 2.94, 3.2, 3.38, 3.53, 3.75, 4.06" << endl << endl;

    // Perform Lagrange interpolation
    methodLagrange(0.75, X, Y);

    // Perform Newton interpolation
    double h = X[1] - X[0];
    double result = newtone(X[0], h, Y, 6, 0.75);
    cout << "\nNewton interpolation result: " << result << endl;

    return 0;
}


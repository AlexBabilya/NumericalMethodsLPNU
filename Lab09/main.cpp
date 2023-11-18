#include <cmath>
#include <iostream>
#include <stdio.h>

void subtractionRow(double** array, int n, int m, int l, int k, double coefficient) {
    for (int i = 0; i < m; i++) {
        if (k != l)
            array[l][i] = array[l][i] - array[k][i] * coefficient;
    }
}

float sumOfRowS(double** array, int m, int k) {
    int p = 0;
    float res = 0;
    for (int i = 0; i < m; i++) {
        if (i > 1 + k && i < m)
            p++;
        if ((i != k) && (i != m - 1))
            res += array[k][i];
    }
    return res;
}

void swapRow(double** array, int m, int k, int l) {
    float* temp = new float[m];
    if (k != l) {
        for (int i = 0; i < m; i++) {
            temp[i] = array[k][i];
        }
        for (int i = 0; i < m; i++) {
            array[k][i] = array[l][i];
        }
        for (int i = 0; i < m; i++) {
            array[l][i] = temp[i];
        }
    }
    delete[] temp;
}

double sum(double x[6], int stepin) {
    double sum = 0;
    for (int i = 0; i < 6; i++)
        sum += pow(x[i], stepin);
    return sum;
}

double sum(double x[6], double y[6], int stepin) {
    double sum = 0;
    for (int i = 0; i < 6; i++)
        sum += y[i] * pow(x[i], stepin);
    return sum;
}

double* methodGauss(double** array, int n, int m) {
    double** system = new double* [n];
    for (int i = 0; i < n; i++) {
        system[i] = new double[m];
        for (int j = 0; j < m; j++) {
            system[i][j] = array[i][j];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i; j < n; j++) {
            subtractionRow(system, n, m, j, i, system[j][i] / system[i][i]);
        }
    }
    double* X = new double[n];
    for (int i = 1; i <= n; i++) {
        float b = system[n - i][m - 1];
        X[n - i] = (b - sumOfRowS(system, m, n - i)) / system[n - i][n - i];
        for (int j = 0; j < n - i; j++)
            system[j][n - i] *= X[n - i];
    }
    delete (system);
    return X;
}

void method(double x[6], double y[6]) {
    double** one = new double* [2];
    double* oneRes;
    one[0] = new double[3];
    one[1] = new double[3];
    one[0][0] = 6;
    one[0][1] = sum(x, 1);
    one[0][2] = sum(x, y, 0);
    one[1][0] = sum(x, 1);
    one[1][1] = sum(x, 2);
    one[1][2] = sum(x, y, 1);
    oneRes = methodGauss(one, 2, 3);
    printf("---------------------------------------------------------\n");
    printf("System of linear polynomial:\n\n");
    std::cout << one[0][0] << "a0 + " << one[0][1] << "a1 = " << one[0][2] << std::endl << std::endl;
    std::cout << one[1][0] << "a1 + " << one[1][1] << "a2 = " << one[1][2] << std::endl << std::endl;
    printf("Linear polynomial:\n\n");
    std::cout << oneRes[0] << "+" << "(" << oneRes[1] << ")" << "x" << std::endl;
    printf("---------------------------------------------------------");
    
    double** two = new double* [3];
    double* twoRes;
    for (int i = 0; i < 3; i++)
        two[i] = new double[4];
    two[0][0] = 6;
    two[0][1] = sum(x, 1);
    two[0][2] = sum(x, 2);
    two[0][3] = sum(x, y, 0);
    two[1][0] = sum(x, 1);
    two[1][1] = sum(x, 2);
    two[1][2] = sum(x, 3);
    two[1][3] = sum(x, y, 1);
    two[2][0] = sum(x, 2);
    two[2][1] = sum(x, 3);
    two[2][2] = sum(x, 4);
    two[2][3] = sum(x, y, 2);
    twoRes = methodGauss(two, 3, 4);
    printf("\nSystem of quadratic polynomial:\n\n");
    std::cout << two[0][0] << "a0 + " << two[0][1] << "a1 + " << two[0][2] << "a2 = " << two[0][3] << std::endl << std::endl;
    std::cout << two[1][0] << "a1 + " << two[1][1] << "a2 + " << two[1][2] << "a3 = " << two[1][3] << std::endl << std::endl;
    std::cout << two[2][0] << "a2 + " << two[2][1] << "a3 + " << two[2][2] << "a4 = " << two[2][3] << std::endl << std::endl;
    printf("Quadratic polynomial:\n\n");
    std::cout << twoRes[0] << "+" << "(" << twoRes[1] << ")" << "x" << "+" << "(" << twoRes[2] << ")" << "x^2" << std::endl;
    printf("---------------------------------------------------------");
    
    double** three = new double* [4];
    double* threeRes;
    for (int i = 0; i < 4; i++)
        three[i] = new double[5];
    three[0][0] = 6;


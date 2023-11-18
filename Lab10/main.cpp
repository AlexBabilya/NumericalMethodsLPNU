#include <cmath>
#include <iostream>
#include <stdio.h>

double y(double x) {
    return sqrt(x) * sin(x * 1.04) * sin(x * 1.04);
}

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

void quadro(double a, double b) {
    double h = (b - a) / 10;
    double x = a;
    double sum[11];
    double sumMed[11];
    double sumL = 0, sumR = 0, sumM = 0;

    printf("Array of points:\n");
    for (int i = 0; i < 11; i++) {
        sum[i] = y(x);
        sumMed[i] = y(x + h / 2);
        x += h;
        printf("%lf ", sum[i]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        sumL += sum[i];
    }
    printf("Result of left side:");
    printf("\n%lf", sumL * h);

    for (int i = 1; i <= 10; i++) {
        sumR += sum[i];
    }
    printf("\nResult of right side:");
    printf("\n%lf", sumR * h);

    for (int i = 0; i < 10; i++) {
        sumM += sumMed[i];
    }
    printf("\nResult of middle:");
    printf("\n%lf", sumM * h);
}

void trapec(double a, double b) {
    double h = (b - a) / 10, x = a;
    double sumA[11];
    double sum = 0;

    for (int i = 0; i < 11; i++) {
        sumA[i] = y(x);
        x += h;
    }

    for (int i = 1; i < 10; i++)
        sum += sumA[i];

    sum += (sumA[0] + sumA[10]) / 2;

    printf("\nResult of trapezoid:");
    printf("\n%lf", sum * h);
}

void simpson(double a, double b) {
    double h = (b - a) / 10, x = a;
    double sumA[11];
    double sum = 0;

    for (int i = 0; i < 11; i++) {
        sumA[i] = y(x);
        x += h;
    }

    for (int i = 0; i < 10; i++) {
        sum += (sumA[i] + 4 * sumA[i + 1] + sumA[i + 2]);
        i++;
    }

    printf("\nResult of Simpson:");
    printf("\n%lf", sum * h / 3);
}

int main() {
    quadro(0, 3);
    trapec(0, 3);
    simpson(0, 3);
    return 0;
}


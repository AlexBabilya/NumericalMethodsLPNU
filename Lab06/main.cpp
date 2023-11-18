#define CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <iostream>
#define I 5
#define J 3
#define R 5

void Print(double** A, double* B, int n1, int n2)
{
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
            printf("%+.3lf ", A[i][j]);
        printf("= %+.3lf\n", B[i]);
    }
    printf("\n");
}

void Show(double** A, int n1, int n2)
{
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
            printf("%+.3lf ", A[i][j]);
        printf("\n");
    }
    printf("\n");
}

double** Multiplication(double A[3][3])
{
    int n = 3;
    int m = 3;
    double** N = new double* [n];
    for (int i = 0; i < n; i++)
        N[i] = new double[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            N[i][j] = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int r = 0; r < R; r++)
                N[i][j] += A[r][i] * A[r][j];
    return N;
}

double* Multiplication(double A[3][3], double B[3])
{
    int n = 3;
    double* C = new double[n];
    for (int i = 0; i < n; i++)
        C[i] = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < R; j++)
            C[i] += A[j][i] * B[j];
    return C;
}

double** L(double** N)
{
    int n = 3;
    int m = 3;
    double** L = new double* [n];
    for (int i = 0; i < n; i++)
        L[i] = new double[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            L[i][j] = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j <= i; j++)
        {
            if (i == j)
            {
                L[i][j] = N[i][j];
                for (int r = 0; r < i; r++)
                    L[i][j] -= pow(L[i][r], 2);
                L[i][j] = sqrt(L[i][j]);
            }
            else if (j == 0)
                L[i][j] = N[i][j] / L[0][0];
            else
            {
                L[i][j] = N[i][j];
                for (int r = 0; r < j; r++)
                    L[i][j] -= L[i][r] * L[j][r];
                L[i][j] = L[i][j] / L[j][j];
            }
        }
    return L;
}

double* Y(double** L, double* C)
{
    int n = 3;
    double* Y = new double[n];
    for (int i = 0; i < n; i++)
        Y[i] = 0;
    for (int i = 0; i < 3; i++)
    {
        Y[i] = C[i];
        for (int m = 0; m <= i - 1; m++)
            Y[i] = Y[i] - L[i][m] * Y[m];
        Y[i] = Y[i] / L[i][i];
    }
    return Y;
}

void Transpon(double** A)
{
    int n = 3;
    int m = 3;
    double** Temp = new double* [n];
    for (int i = 0; i < n; i++)
        Temp[i] = new double[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Temp[i][j] = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Temp[i][j] = A[j][i];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            A[i][j] = Temp[i][j];
    delete[] Temp;
}

double* X(double** L, double* Y)
{
    int n = 3;
    double* X = new double[n];
    for (int i = 0; i < n; i++)
        X[i] = 0;
    for (int i = 2; i >= 0; i--)
    {
        X[i] = Y[i];
        for (int m = i + 1; m < 3; m++)
            X[i] -= L[i][m] * X[m];
        X[i] = X[i] / L[i][i];
    }
    return X;
}

int main() {
    double A[I][J] = {
        {3, 1, -1},
        {-5, 1, 3},
        {2, 0, 1},
        {1, -5, 3},
        {2, -4, -1}
    };
    double B[I] = {2, -10, 1, 7, 11};
    double** N = Multiplication(A);
    double* C = Multiplication(A, B);

    printf("C matrix:\n");
    for (int i = 0; i < R; i++)
        printf("%lf\n", C[i]);

    printf("\nN matrix:\n");
    Show(N, 3, 3);

    double** _L = L(N);
    printf("L matrix:\n");
    Show(_L, 3, 3);

    double* _Y = Y(_L, C);
    printf("Y matrix:\n");
    for (int i = 0; i < R; i++)
        printf("%lf\n", _Y[i]);

    printf("\nLX=Y:\n");
    Print(_L, _Y, 3, 3);

    Transpon(_L);

    double* _X = X(_L, _Y);
    for (int i = 0; i < 3; i++)
        printf("X%i = %f\n", i

 + 1, _X[i]);

    return 0;
}


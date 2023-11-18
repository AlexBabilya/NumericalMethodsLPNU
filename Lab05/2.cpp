#include <stdio.h>
#include <math.h>
#define N 4

int check(double X[N][1], double x[N][1], double e)
{
    int check = 1;
    double sum = 0;

    for (int i = 0; i < N; i++)
    {
        sum += pow(X[i][0] - x[i][0], 2);
    }

    if (sqrt(sum) < e)
    {
        check = 0;
    }

    return check;
}

void beta(double B[N][1], double A[N][N + 1])
{
    for (int i = 0; i < N; i++)
    {
        B[i][0] = A[i][N] / A[i][i];
    }
}

void alpha(double alpha[N][N], double A[N][N + 1])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i != j)
                alpha[i][j] = -A[i][j] / A[i][i];
            else
                alpha[i][j] = 0;
        }
    }
}

void MethodZeidel(double A[N][N + 1], double e)
{
    double B[N][1];
    double Ap[N][N];
    double X1[N][1];
    double X0[N][1];
    int count = 0;

    beta(B, A);
    alpha(Ap, A);

    for (int i = 0; i < N; i++)
        X1[i][0] = B[i][0];

    for (int i = 0; i < N; i++)
        X0[i][0] = 0;

    printf("Method Zeidel:\n|");

    for (int i = 0; i < N; i++)
        printf("\tX%i\t|", i + 1);

    printf("\n");

    while (1)
    {
        for (int i = 0; i < N; i++)
        {
            for (int i = 0; i < N; i++)
                X0[i][0] = X1[i][0];

            X1[i][0] = B[i][0];

            for (int j = 0; j <= i - 1; j++)
                X1[i][0] = X1[i][0] + Ap[i][j] * X0[j][0];

            for (int j = i + 1; j < N; j++)
                X1[i][0] = X1[i][0] + Ap[i][j] * X0[j][0];
        }

        for (int i = 0; i < N; i++)
        {
            printf("|%+lf", X1[i][0]);
            count++;
        }

        printf("|\n");

        if (!check(X1, X0, e))
        {
            printf("Answer:\n");
            printf("|");

            for (int i = 0; i < N; i++)
                printf("\tX%i\t|", i + 1);

            printf("\n");

            for (int i = 0; i < N; i++)
                printf("|%+lf", X1[i][0]);

            printf("|\n\n");

            printf("Total iteration %d", count);
            break;
        }
    }
}

int main()
{
    double A[N][N + 1] = {
        {0.23, -0.04, 0.21, -0.18, -1.24},
        {0.45, -0.23, 0.06, 0, 0.88},
        {0.26, 0, 0.34, -0.11, -0.62},
        {0.05, -0.26, 0.34, -1.12, 1.17}};
    double e = 0.0001;

    MethodZeidel(A, e);

    return 0;
}


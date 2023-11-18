#include <stdio.h>
#include <math.h>

float determinant33(float a[3][3]) {
    return a[0][0] * a[1][1] * a[2][2] + a[2][0] * a[0][1] * a[1][2] + a[0][2] * a[1][0] * a[2][1] -
           a[2][0] * a[1][1] * a[0][2] - a[0][1] * a[1][0] * a[2][2] - a[0][0] * a[1][2] * a[2][1];
}

float determinant22(float a[2][2]) {
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}

float minor(float A[3][3], int k, int l, float z) {
    float B[2][2];
    int m = 0, n = 0;

    printf("\nMinor %d %d:\n", k, l);
    for (int i = 0; i < 2; i++) {
        n = 0;
        if (m == k)
            i--;
        else {
            for (int j = 0; j < 2; j++) {
                if (n != l) {
                    B[i][j] = A[m][n];
                    printf("%+2.2f ", B[i][j]);
                } else
                    j--;
                n++;
            }
            printf("\n");
        }
        m++;
    }

    return pow(-1, k + l + 2) * determinant22(B) / z;
}

void showMatrix(float A[][4], int i, int j) {
    printf("\n");
    for (int m = 0; m < i; m++) {
        for (int n = 0; n < j; n++)
            printf("%2.3f ", A[m][n]);
        printf("\n");
    }
    printf("\n");
}

void multiply(float array[3][3], float a[3][1]) {
    float X[3][1] = {0};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 1; j++)
            for (int k = 0; k < 3; k++)
                X[i][j] += array[i][k] * a[k][j];

    a[0][0] = X[0][0];
    a[1][0] = X[1][0];
    a[2][0] = X[2][0];
}

void inverse(float A[3][3]) {
    float B[3][3];
    float k = determinant33(A);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            B[j][i] = minor(A, i, j, k);

    printf("\nInverse matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = B[i][j];
            printf("%+2.2f ", B[i][j]);
        }
        printf("\n");
    }
}

void changeVerticalRow(float A[3][3], float array[3][4], int l) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            A[i][j] = (j != l) ? array[i][j] : array[i][3];
}

void methodKramer(float array[3][4]) {
    float A[3][3], A1[3][3], A2[3][3], A3[3][3];

    printf("Kramer method:\n\n");

    changeVerticalRow(A, array, 3);
    printf("Determinant of A=%f\n", determinant33(A));

    changeVerticalRow(A1, array, 0);
    printf("Determinant of A1=%f\n", determinant33(A1));

    changeVerticalRow(A2, array, 1);
    printf("Determinant of A2=%f\n", determinant33(A2));

    changeVerticalRow(A3, array, 2);
    printf("Determinant of A3=%f\n\n");

    printf("X1=A1/A=%+2.4f\n", determinant33(A1) / determinant33(A));
    printf("X2=A2/A=%+2.4f\n", determinant33(A2) / determinant33(A));
    printf("X3=A3/A=%+2.4f\n", determinant33(A3) / determinant33(A));
}

void methodInverse(float array[3][4]) {
    printf("\nInverse method:\n");
    float A[3][3], X[3][1];

    changeVerticalRow(A, array, 3);
    inverse(A);

    for (int i = 0; i < 3; i++)
        X[i][0] = array[i][3];

    multiply(A, X);

    printf("\nX1=%f\n", X[0][0]);
    printf("X2=%f\n", X[1][0]);
    printf("X3=%f\n", X[2][0]);
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <malloc.h>

void showMatrix(float** array, int n, int m) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%f ", array[i][j]);
        printf("\n");
    }
    printf("\n\n---------------------------------------\n");
}

void swapRow(float** array, int m, int k, int l) {
    float* temp = (float*)malloc(m * sizeof(float));
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
    free(temp);
}

float sumOfVectors(float* y, float** l, int n) {
    float s = 0;
    for (int i = 0; i < n; i++) {
        s += l[n][i] * y[i];
        if (l[n][i] * y[i] < 0) {
            printf("-(%f*%f)", l[n][i], y[i]);
        }
    }
    return s;
}

float sumOfVectors2(float* x, float** u, int k, int n) {
    float s = 0;
    for (int i = n - k; i > 0; i--) {
        s += u[k][n - i] * x[n - i];
        printf("-(%f*%f)", u[k][n - i], x[n - i]);
    }
    return s;
}

void chooseElementMatrix(float** array, int n, int j) {
    float max = fabs(array[j][j]);
    for (int i = j; i < n; i++) {
        if (fabs(array[i][j]) > max) {
            max = fabs(array[i][j]);
            swapRow(array, n + 1, j, i);
        }
    }
}

float sumOfRowS(float** array, int m, int k) {
    int p = 0;
    float res = 0;
    for (int i = 0; i < m; i++) {
        if (i > 1 + k && i < m) {
            printf("%f", array[k][i]);
            p++;
        }
        if ((i != k) && (i != m - 1))
            res += array[k][i];
    }
    if (p == 0) {
        printf("0");
    }
    //printf("\n%f\n",res);
    return res;
}

void subtractionRow(float** array, int n, int m, int l, int k, float coefficient) {
    for (int i = 0; i < m; i++) {
        //printf("\n-%f %f- \n", array[l][i], array[k][i]);
        if (k != l)
            array[l][i] = array[l][i] - array[k][i] * coefficient;
    }
}

void methodGauss(float** array, int n, int m) {
    printf("\nGauss method:\n");
    float** system = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        system[i] = (float*)malloc(m * sizeof(float));
        for (int j = 0; j < m; j++) {
            system[i][j] = array[i][j];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        chooseElementMatrix(system, n, i);
        printf("\nThe %ith row:", i);
        for (int j = i; j < n; j++) {
            subtractionRow(system, n, m, j, i, system[j][i] / system[i][i]);
            //printf("\n|%i %i|\n",j,i);
        }
        showMatrix(system, n, m);
    }
    float* X = (float*)malloc(n * sizeof(float));
    printf("Answers:\n");
    for (int i = 1; i <= n; i++) {
        float b = system[n - i][m - 1];
        printf("X%i=(%f-", n - i + 1, b);
        X[n - i] = (b - sumOfRowS(system, m, n - i)) / system[n - i][n - i];
        for (int j = 0; j < n - i; j++)
            system[j][n - i] *= X[n - i];
        printf(")/%f=%f\n", system[n - i][n - i], X[n - i]);
    }
    free(system);
    free(X);
}

void methodLU(float** array, int n, int m) {
    printf("\nLU method:\n");
    float** A = (float**)malloc(n * sizeof(float*));
    float** L = (float**)malloc(n * sizeof(float*));
    float** U = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        A[i] = (float*)malloc(n * sizeof(float));
        U[i] = (float*)malloc(n * sizeof(float));
        L[i] = (float*)malloc(n * sizeof(float));
        for (int j = 0; j < n; j++) {
            A[i][j] = array[i][j];
            L[i][j] = 0;
            if (i == j)
                U[i][j] = 1;
            else
                U[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        L[i][0] = A[i][0];
        U[0][i] = A[0][i] / L[0][0];
    }
    float sum;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i >= j) {
                sum = 0;
                for (int k = 0; k < j; k++)
                    sum += L[i][k] * U[k][j];
                L[i][j] = A[i][j] - sum;
            } else {
                sum = 0;
                for (int k = 0; k < i; k++)
                    sum += L[i][k] * U[k][j];
                U[i][j] = (A[i][j] - sum) / L[i][i];
            }
        }
    }
    printf("\nL matrix:\n");
    showMatrix(L, n, n);
    printf("\nU matrix:\n");
    showMatrix(U, n, n);
    float* Y = (float*)malloc(n * sizeof(float));
    Y[0] = array[0][n] / L[0][0];
    printf("\nY1=%f/%f=%f\n", array[0][n], L[0][0], Y[0]);
    for (int i = 1; i < n; i++) {
        printf("\nY%i=1/%f*(%f)", i + 1, L[i][i], array[i][n]);
        Y[i] = 1 / L[i][i] * (array[i][n] - sumOfVectors(Y, L, i));
        printf("=%f\n", Y[i]);
    }
    float* X = (float*)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        X[i] = 0;
    }
    X[n - 1] = Y[n - 1];
    printf("\n---------------------------------------\n");
    printf("\nAnswers:\n");
    printf("\nX%i=Y%i=%f\n", n, n, X[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
        printf("\nX%i=%f", i + 1, Y[i]);
        X[i] = Y[i] - sumOfVectors2(X, U, i, n);
        printf("=%f\n", X[i]);
    }
}

int main() {
    int n = 3, m = 4;
    float** systemS = NULL;
    int flag;
    printf("What do you prefer?\nStandart matrix(0)\nInput from console(1)\nInput from file(2)\n");
    scanf_s("%i", &flag);
    if (flag == 0) {
        systemS = (float**)malloc(n * sizeof(float*));
        for (int i = 0; i < n; i++) {
            systemS[i] = (float*)malloc(m * sizeof(float));
        }
        systemS[0][0] = 0.65;
        systemS[0][1] = -0.93;
        systemS[0][2] = 0.45;
        systemS[0][3] = -0.72;
        systemS[1][0] = 1.15;
        systemS[1][1] = 0.43;
        systemS[1][2] = -0.72;
        systemS[1][3] = 1.24;
        systemS[2][0] = 0.56;
        systemS[2][1] = -0.18;
        systemS[2][2] = 1.03;
        systemS[2][3] = 2.25;
    }
    if (flag == 1) {
        printf("Enter the amount of X: ");
        scanf("%i", &n);
        m = n + 1;
        systemS = (float**)malloc(n * sizeof(float*));
        for (int i = 0; i < n; i++) {
            systemS[i] = (float*)malloc(m * sizeof(float));
            for (int j = 0; j < m; j++) {
                scanf("%f ", &systemS[i][j]);
            }
        }
    }
    if (flag == 2) {
        char fln[25];
        printf("\nEnter the name of file: ");
        scanf("%s", &fln);
        FILE* fl;
        fl = fopen(fln, "r");
        printf("Enter the amount of X: ");
        scanf("%i", &n);
        m = n + 1;
        systemS = (float**)malloc(n * sizeof(float*));
        for (int i = 0; i < n; i++) {
            systemS[i] = (float*)malloc(m * sizeof(float));
            for (int j = 0; j < m; j++) {
                if (fscanf(fl, "%f", &systemS[i][j]) != EOF) {
                    fscanf(fl, "%f", &systemS[i][j]);
                } else {
                    printf("Invalid format. Check your matrix");
                    return 0;
                }
            }
        }
    }
    printf("\nYour matrix is:\n");
    showMatrix(systemS, n, m);
    printf("\n=======================================\n");
    methodGauss(systemS, n, m);
    printf("\n=======================================\n");
    methodLU(systemS, n, m);
    printf("\n=======================================\n");
}


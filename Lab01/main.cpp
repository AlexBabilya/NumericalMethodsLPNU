// main.c

#include <stdio.h>
#include <math.h>
#include "func.h"

int main() {
    float array[3][4] = {
        {0.65, -0.93, 0.45, -0.72},
        {1.15, 0.43, -0.72, 1.24},
        {0.56, -0.18, 1.03, 2.25}
    };

    printf("System of equations (matrix A):\n");
    showMatrix(array, 3, 4);

    if (determinant33(array) == 0) {
        printf("Determinant = 0, the system does not have any answers\nEnter the new numbers:\n");

        while (determinant33(array) == 0) {
            scanf_s("%f %f %f %f", &array[0][0], &array[0][1], &array[0][2], &array[0][3]);
            scanf_s("%f %f %f %f", &array[1][0], &array[1][1], &array[1][2], &array[1][3]);
            scanf_s("%f %f %f %f", &array[2][0], &array[2][1], &array[2][2], &array[2][3]);
        }
    }

    methodKramer(array);
    printf("\n----------------------------------\n");
    methodInverse(array);

    return 0;
}


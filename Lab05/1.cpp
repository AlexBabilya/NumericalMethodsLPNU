#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

void main()
{
    float a[20][20], x[20], e, big, temp, relerror, sum;
    int n, i, j, maxit, itr;
    char ch;
    
    printf("\n\nENTER THE SIZE OF THE EQUATION :: ");
    scanf_s("%d", &n);
    
    for (i = 1; i <= n; i++)
    {
        printf("\n\nEnter the coefficients of equation %d and RHS \n", i);
        for (j = 1; j <= n + 1; j++)
            scanf_s("%f", &a[i][j]);
    }

    printf("\n\nEnter relative error and the number of iterations :: ");
    scanf_s("%f%d", &e, &maxit);

    for (i = 1; i <= n; i++)
        x[i] = 0;

    for (itr = 1; itr <= maxit; itr++)
    {
        big = 0;

        for (i = 1; i <= n; i++)
        {
            sum = 0;

            for (j = 1; j <= n; j++)
            {
                if (i != j)
                    sum = sum + a[i][j] * x[j];
            }

            temp = (a[i][n + 1] - sum) / a[i][i];
            relerror = fabs((x[i] - temp) / temp);

            if (relerror > big)
                big = relerror;

            x[i] = temp;
            printf("%.4f \t|%.4f \t|%.4f \t|%.4f \t\n", x[1], x[2], x[3], x[4]);
        }

        if (big <= e)
        {
            printf("Converges to a solution in %d iterations\n", itr);

            for (i = 1; i <= n; i++)
                printf("\nx[%d] = %.4f\t", i, x[i]);

            exit(1);
        }
    }

    printf("Does not converge in %d iterations \n", maxit);
}


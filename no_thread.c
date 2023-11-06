#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double f(double x) { return sqrt(1.0 - x * x); }

int main()
{
    int devisions = 1e8;
    double upper = 1.0;
    double lower = 0.0;
    double width = (upper - lower) / devisions;

    double upper_sum = 0.0;
    double lower_sum = 0.0;

    for (int i = 0; i < devisions; i++)
    {
        upper_sum += f(lower + (i + 1) * width) * width;
        lower_sum += f(lower + i * width) * width;
    }

    printf("upper pi_value: %0.15lf\n", upper_sum * 4);
    printf("lower pi_value: %0.15lf\n", lower_sum * 4);

    return 0;
}
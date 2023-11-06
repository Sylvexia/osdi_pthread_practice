#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define DIVISIONS 100000000

double f(double x) { return sqrt(1.0 - x * x); }

int main()
{
    double upper = 1.0;
    double lower = 0.0;
    double width = (upper - lower) / DIVISIONS;

    double lower_sum = 0.0;
    double upper_sum = 0.0;

    int maxCPU = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of available CPU: %d\n", maxCPU);
    int numCPU = maxCPU;
    printf("Number of running CPU: %d\n", numCPU);


    #pragma omp parallel for num_threads(numCPU) reduction(+:upper_sum, lower_sum)
    for (int i = 0; i < DIVISIONS; i++)
    {
        lower_sum += f(lower + i * width) * width;
        upper_sum += f(lower + (i + 1) * width) * width;
    }

    printf("lower pi_value: %0.15lf\n", lower_sum * 4);
    printf("upper pi_value: %0.15lf\n", upper_sum * 4);

    return 0;
}
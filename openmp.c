#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <omp.h>

const double f(const double x) { return sqrt(1.0 - x * x); }

int main(int argc, char *argv[])
{
    int opt;
    long long int division = 1e9;
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of available CPU: %d\n", numCPU);

    while ((opt = getopt(argc, argv, "t:n:")) != -1)
    {
        switch (opt)
        {
        case 't':
            numCPU = atoi(optarg);
            break;
        case 'n':
            division = atoll(optarg);
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-t num_threads] [-n n_division]\n", argv[0]);
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr, "Unknown option: %c\n", optopt);
            exit(EXIT_FAILURE);
        }
    }

    if (optind < argc)
    {
        printf("Non-option arguments: ");
        for (int i = optind; i < argc; i++)
        {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }

    printf("Number of running CPU: %d\n", numCPU);
    printf("Number of division: %lld\n", division);

    if (numCPU < 1)
    {
        printf("Number of threads must be greater than 0\n");
        exit(EXIT_FAILURE);
    }
    if (division < 1)
    {
        printf("Number of division must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    double lower_sum = 0, upper_sum = 0;
    double width = 1.0 / division;

#pragma omp parallel for num_threads(numCPU) reduction(+ : upper_sum, lower_sum)
    for (long long int i = 0; i < division; i++)
    {
        upper_sum += f(i * width) * width;
        lower_sum += f((i + 1) * width) * width;
    }

    printf("division the fuck: %lld\n", division);

    printf("upper pi_value: %0.15lf\n", upper_sum * 4);
    printf("lower pi_value: %0.15lf\n", lower_sum * 4);

    return 0;
}
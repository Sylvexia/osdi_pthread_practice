#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

const double f(const double x) { return sqrt(1.0 - x * x); }

int main(int argc, char* argv[])
{
    int opt;
    long long int division = 1e9;

    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            division = atoll(optarg);
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-n n_division]\n", argv[0]);
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

    printf("Number of division: %lld\n", division);

    if (division < 1)
    {
        printf("Number of division must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    double lower_sum = 0, upper_sum = 0;
    double width = 1.0 / division;

    for (long long int i = 0; i < division; i++)
    {
        lower_sum += f((i + 1) * width) * width;
        upper_sum += f(i * width) * width;
    }

    printf("upper pi_value: %0.15lf\n", upper_sum * 4);
    printf("lower pi_value: %0.15lf\n", lower_sum * 4);

    return 0;
}
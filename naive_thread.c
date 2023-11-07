#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <getopt.h>

typedef struct ThreadParams
{
    int numCPU;
    int id;
    long long int division;
    double local_lower_sum;
    double local_upper_sum;
} ThreadParams;

const double f(const double x) { return sqrt(1.0 - x * x); }

void cal_pi(void *args)
{
    ThreadParams *params = (struct ThreadParams *)args;

    int numCPU = params->numCPU;
    int thread_id = params->id;
    long long int division = params->division;
    // printf("Thread %d is running\n", thread_id);

    double width = 1.0 / division;

    long long int start = thread_id * (division / numCPU);
    long long int end = ((thread_id + 1) * (division / numCPU));
    // printf("Thread %d is calculating from %d to %d\n", thread_id, start, end);
    if (end > division)
        end = division;

    double local_upper = f((start) * width) * width;
    double local_lower = 0.0;
    for (; start < end; start++)
    {
        params->local_upper_sum += local_upper;
        local_lower = f((start + 1) * width) * width;
        params->local_lower_sum += local_lower;
        local_upper = local_lower;
    }
}

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

    if(numCPU < 1)
    {
        printf("Number of threads must be greater than 0\n");
        exit(EXIT_FAILURE);
    }
    if(division < 1)
    {
        printf("Number of division must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    ThreadParams *thread_params = (ThreadParams *)malloc(sizeof(ThreadParams) * numCPU);
    pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * numCPU);

    for (long i = 0; i < numCPU; i++)
    {
        thread_params[i].id = i;
        thread_params[i].numCPU = numCPU;
        thread_params[i].division = division;
        thread_params[i].local_lower_sum = 0.0;
        thread_params[i].local_upper_sum = 0.0;
        pthread_create(&tid[i], NULL, (void *)cal_pi, &thread_params[i]);
    }

    for (int i = 0; i < numCPU; i++)
        pthread_join(tid[i], NULL);

    double lower_sum = 0, upper_sum = 0;

    for (int i = 0; i < numCPU; i++)
    {
        upper_sum += thread_params[i].local_upper_sum;
        lower_sum += thread_params[i].local_lower_sum;
    }

    printf("upper pi_value: %0.15lf\n", upper_sum * 4);
    printf("lower pi_value: %0.15lf\n", lower_sum * 4);

    return 0;
}
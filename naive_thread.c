#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define DIVISIONS 100000000

const double upper = 1.0;
const double lower = 0.0;
double width = (upper - lower) / DIVISIONS;

double upper_sum = 0.0;
double lower_sum = 0.0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double f(double x) { return sqrt(1.0 - x * x); }

void cal_pi(void)
{
    for (int i = 0; i < DIVISIONS; i++)
    {
        pthread_mutex_lock(&mutex);
        upper_sum += f(lower + (i + 1) * width) * width;
        lower_sum += f(lower + i * width) * width;
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    int maxCPU = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of available CPU: %d\n", maxCPU);
    int numCPU = maxCPU / 2;
    printf("Number of current CPU: %d\n", numCPU);
    pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * numCPU);

    for (long i = 0; i < numCPU; i++)
        pthread_create(&tid[i], NULL, (void *)cal_pi, (void *)i);

    for (int i = 0; i < numCPU; i++)
        pthread_join(tid[i], NULL);

    printf("upper pi_value: %0.15lf\n", upper_sum * 4 / numCPU);
    printf("lower pi_value: %0.15lf\n", lower_sum * 4 / numCPU);

    return 0;
}
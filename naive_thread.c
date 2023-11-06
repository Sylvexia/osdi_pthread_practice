#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct ThreadParams
{
    int param1;
    char param2;
};

double upper_sum = 0.0;
double lower_sum = 0.0;

double f(double x) { return sqrt(1.0 - x * x); }

void cal_pi(void *arg)
{
    int thread_id = (intptr_t)arg;
    // printf("Thread %d is running\n", thread_id);

    int start = thread_id * (DIVISIONS / numCPU);
    int end = ((thread_id + 1) * (DIVISIONS / numCPU));
    // printf("Thread %d is calculating from %d to %d\n", thread_id, start, end);
    if (end > DIVISIONS)
        end = DIVISIONS;

    double local_lower_sum = 0.0;
    double local_upper_sum = 0.0;

    for (; start < end; start++)
    {
        local_lower_sum += f(lower + start * width) * width;
        local_upper_sum += f(lower + (start + 1) * width) * width;
    }

    pthread_mutex_lock(&mutex);
    lower_sum += local_lower_sum;
    upper_sum += local_upper_sum;
    pthread_mutex_unlock(&mutex);
}

int main()
{
    int devision = 100000000;
    const double upper = 1.0;
    const double lower = 0.0;
    double width = (upper - lower) / devision;
    int numCPU = 0;

    int maxCPU = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of available CPU: %d\n", maxCPU);

    numCPU = maxCPU;
    printf("Number of running CPU: %d\n", numCPU);
    pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * numCPU);

    for (long i = 0; i < numCPU; i++)
        pthread_create(&tid[i], NULL, (void *)cal_pi, (void *)i);

    for (int i = 0; i < numCPU; i++)
        pthread_join(tid[i], NULL);

    printf("lower pi_value: %0.15lf\n", lower_sum * 4);
    printf("upper pi_value: %0.15lf\n", upper_sum * 4);

    pthread_mutex_destroy(&mutex);

    return 0;
}
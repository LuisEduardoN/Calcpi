#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "calcpi.h"

double *somatoria;

void *calcPI(void *args)
{
    valores *v = (valores *)args;
    long divisao = v->nSerie / v->nThreads;
    long inicio = v->i * divisao;
    long fim = inicio + divisao;
    if ((v->i) == (v->nThreads - 1))
    {
        fim = v->nSerie;
    }
    somatoria[v->i] = 0;
    for (long i = inicio; i < fim; i++)
    {
        somatoria[v->i] += ((i % 2 == 0) ? 1.0 : -1.0) / (2 * i + 1);
    }
}

void createAndJoinThreads(valores *v, pthread_t *threads_ids)
{
    for (int i = 0; i < v->nThreads; i++)
    {
        v[i].i = i;
        pthread_create(&threads_ids[i], NULL, calcPI, (void *)&v[i]);
    }
    for (int i = 0; i < v->nThreads; i++)
    {
        pthread_join(threads_ids[i], NULL);
    }
}

int main()
{

    long nSerie = 1000000000;
    int nThreads[6] = {1, 2, 4, 8, 16, 32};
    double pi;
    double executionTimes[5], timesAvg = 0.0;
    struct timeval start, end;

    for (int z = 0; z < 6; z++)
    {
        valores *v = (valores *)malloc((nThreads[z]) * sizeof(valores));
        somatoria = (double *)calloc(nThreads[z], sizeof(double));

        for (int i = 0; i < nThreads[z]; i++)
        {
            v[i].nThreads = nThreads[z];
            v[i].nSerie = nSerie;
        }

        pthread_t threads_ids[nThreads[z]];

        for (int i = 0; i < 5; i++)
        {
            gettimeofday(&start, NULL);
            createAndJoinThreads(v, threads_ids);
            gettimeofday(&end, NULL);
            executionTimes[i] = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        }

        free(v);

        for (int i = 0; i < 5; i++)
        {
            timesAvg += executionTimes[i];
        }
        timesAvg /= 5;
        

        printf("Tempo médio de execução com %d threads: %.3f segundos\n\n", nThreads[z], timesAvg);

        double somatoriaTotal = 0;
        for (int i = 0; i < nThreads[z]; i++)
        {
            somatoriaTotal += somatoria[i];
        }

        pi = somatoriaTotal*4.0;
        free(somatoria);
    }
        printf("Valor de pi calculado: %.20f\n",pi);
        printf("Valor de pi real:      %.20f\n", M_PI);
    return 0;
}

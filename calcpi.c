#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "calcpi.h"

double *somatoria;

void* calcPI(void* args){
    valores *v = (valores*) args;    
    long divisao = v->nSerie/v->nThreads;
    long inicio = v->i * divisao;
    long fim = inicio + divisao;
    if ((v->i)==(v->nThreads-1))
    {
        fim = v->nSerie;
    }
    for (long i = inicio; i < fim; i++)
    {
        somatoria[v->i] += ( (i%2==0) ? 1.0 : -1.0) / (2*i+1);
    }
    
}

void createAndJoinThreads(valores* v, pthread_t* threads_ids) {
    for (int i = 0; i < v->nThreads; i++) {
        v[i].i = i;
        pthread_create(&threads_ids[i], NULL, calcPI, (void*)&v[i]);
    }
    for (int i = 0; i < v->nThreads; i++) {
        pthread_join(threads_ids[i], NULL);
    }
}

int main()
{   
    
    long nSerie = 10000000000;
    int nThreads;
    double pi;
    struct timeval start, end;
    

    printf("Digite o número de threads: ");
    scanf("%d",&nThreads);
    
    valores *v = (valores*)malloc((nThreads)*sizeof(valores));
    somatoria = (double*)calloc(nThreads, sizeof(double));
    
    for (int i = 0; i < nThreads; i++) {
        v[i].nThreads = nThreads;
        v[i].nSerie = nSerie;
    }
    
    pthread_t threads_ids[nThreads];

    gettimeofday(&start,NULL);
    createAndJoinThreads(v, threads_ids);
    gettimeofday(&end,NULL);

    free(v);
    
    double timeInSeconds = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Tempo de execução com %d threads: %.2f segundos\n",nThreads,timeInSeconds);
    
    double somatoriaTotal = 0;
    for (int i = 0; i < nThreads; i++)
    {
        somatoriaTotal+=somatoria[i];
    }
    
    printf("Valor de pi calculado: %.20f\n",somatoriaTotal*4);
    printf("Valor de pi real: %.20f\n",M_PI);

    free(somatoria);

    return 0;
}

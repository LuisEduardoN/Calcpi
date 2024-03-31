#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
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

void createAndJoinThreads(int nThreads, valores* v, pthread_t* threads_ids) {
    for (int i = 0; i < nThreads; i++) {
        v[i].i = i;
        pthread_create(&threads_ids[i], NULL, calcPI, (void*)&v[i]);
    }
    for (int i = 0; i < nThreads; i++) {
        pthread_join(threads_ids[i], NULL);
    }
}

int main()
{   
    
    long nSerie = 10000000000;
    int nThreads;
    double pi;

    printf("Digite o número de threads: ");
    scanf("%d",&nThreads);
    
    valores *v = (valores*)malloc((nThreads)*sizeof(valores));
    somatoria = (double*)calloc(nThreads, sizeof(double));
    
    for (int i = 0; i < nThreads; i++) {
        v[i].nThreads = nThreads;
        v[i].nSerie = nSerie;
    }
    
    pthread_t threads_ids[nThreads];
    createAndJoinThreads(nThreads, v, threads_ids);

    free(v);
    
    double somatoriaTotal = 0;
    for (int i = 0; i < nThreads; i++)
    {
        somatoriaTotal+=somatoria[i];
    }
    
    printf("Valor de pi calculado: %.25f\n",somatoriaTotal*4);

    free(somatoria);

    return 0;
}

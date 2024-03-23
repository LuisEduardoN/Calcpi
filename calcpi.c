#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include "calcpi.h"

double *somatoria;

void divideWork(long nSerie, int nThreads, int* listaNSerie){
    listaNSerie[0] = 0;
    int division = nSerie/nThreads;
    for (int i = 1; i <= nThreads; i++)
    {
        listaNSerie[i] = listaNSerie[i-1]+division;
    }
}


void* calcPI(void* args){
    sleep(5);
    valores *v = (valores*) args;    
    int inicio = v->inicio;
    int fim = v->fim;
    for(int j = inicio; j<(fim); j++){
        somatoria[v->i] = somatoria[v->i] + pow(-1,j)/(2.0*j+1);
    }
}

int main(int argc, char const *argv[])
{   
    
    long nSerie;
    int nThreads;
    double pi;

    printf("Digite o número de série: ");
    scanf("%ld",&nSerie);

    printf("Digite o número de threads: ");
    scanf("%d",&nThreads);

    int *seriesDivided = (int*)malloc((nThreads + 1) * sizeof(int));
    valores *v = (valores*)malloc((nThreads)*sizeof(valores));
    somatoria = (double*)malloc(nThreads*sizeof(double));    

    divideWork(nSerie,nThreads,seriesDivided);
    
    
    pthread_t threads_ids[nThreads];

    for (int i = 0; i < nThreads; i++)
    {
        v[i].inicio = seriesDivided[i];
        v[i].fim = seriesDivided[i+1];
        v[i].i = i;
        pthread_create(&threads_ids[i],NULL, calcPI,(void*)&v[i]);
    }

    for (int i = 0; i < nThreads; i++)
    {
        pthread_join(threads_ids[i],NULL);
    }

    free(seriesDivided);

    double somatoriaTotal = 0;
    
    for (int i = 0; i < nThreads; i++)
    {   
        somatoriaTotal = somatoriaTotal + somatoria[i];
    }

    free(somatoria);

    pi = somatoriaTotal*4;
    printf("Valor de pi calculado: %.15f\n",pi);
    printf("Valor de pi real: %.15f\n",M_PI);

    return 0;
}

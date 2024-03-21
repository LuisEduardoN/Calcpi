#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double somatoria = 0;

void divideWork(long nSerie, int nThreads, int* listaNSerie){
    listaNSerie[0] = 0;
    int division = nSerie/nThreads;
    for (int i = 1; i <= nThreads; i++)
    {
        listaNSerie[i] = listaNSerie[i-1]+division;
    }
}

void calcPI(int *listaNSerie, int len){
    int iterateNumber = listaNSerie[1]-listaNSerie[0];
    int k = 0;
    for (int i = 0; i < len; i++)
    {
        for(int j = k; j<(k+iterateNumber); j++){
            somatoria = somatoria + pow(-1,j)/(2.0*j+1);
        }
        k = k + iterateNumber;
    }
}

int main(int argc, char const *argv[])
{   
    long nSerie;
    int nThreads;
    int *seriesDivided = (int*)malloc((nThreads + 1) * sizeof(int));
    double pi;

    printf("Digite o número de série: ");
    scanf("%ld",&nSerie);

    printf("Digite o número de threads: ");
    scanf("%d",&nThreads);

    divideWork(nSerie,nThreads,seriesDivided);
    
    calcPI(seriesDivided, nThreads+1);

    free(seriesDivided);

    pi = somatoria*4;
    printf("Valor de pi calculado: %.15f\n",pi);
    printf("Valor de pi real: %.15f\n",M_PI);

    return 0;
}

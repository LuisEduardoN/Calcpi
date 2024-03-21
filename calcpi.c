#include <stdio.h>
#include <math.h>

double somatoria = 0;

void divideWork(int nSerie, int nThreads, int* listaNSerie){
    listaNSerie[0] = 0;
    int division = nSerie/nThreads;
    for (int i = 1; i <= nThreads; i++)
    {
        listaNSerie[i] = listaNSerie[i-1]+division;
    }
}

void calcPI(int *listaNSerie){

    int len = sizeof(listaNSerie)/sizeof(listaNSerie[0]);
    int itererateNumber = listaNSerie[1]-listaNSerie[0];
    int k = 0;
    for (int i = 0; i < len; i++)
    {
        for(int j = k; j<(listaNSerie[i+1]); j++){
            somatoria = somatoria + pow(-1,j)/(2.0*j+1);
        }
        k = k + itererateNumber;
    }
}

int main(int argc, char const *argv[])
{   
    int nSerie, nThreads;
    int seriesDivided[nThreads+1];
    double pi;

    printf("Digite o número de série: ");
    scanf("%d",&nSerie);

    printf("Digite o número de threads: ");
    scanf("%d",&nThreads);

    divideWork(nSerie,nThreads,seriesDivided);
    
    calcPI(seriesDivided);

    pi = somatoria*4;
    printf("Valor de pi: %f\n",pi);

    return 0;
}

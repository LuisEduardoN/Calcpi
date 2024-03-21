#include <stdio.h>
#include <math.h>

double somatoria = 0;

void calcPI(int nSerie){
    for(int i = 0; i<nSerie; i++){
            somatoria = somatoria + pow(-1,i)/(2.0*i+1);
    }
}

int main(int argc, char const *argv[])
{   
    int nSerie;
    double pi;

    printf("Digite o número de série: ");
    scanf("%d",&nSerie);

    calcPI(nSerie);

    pi = somatoria*4;
    printf("Valor de pi: %f\n",pi);

    return 0;
}

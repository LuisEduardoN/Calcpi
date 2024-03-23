#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct args
{
    int inicio;
    int fim;
    int i;
} valores;


void divideWork(long nSerie, int nThreads, int* listaNSerie);
void* calcPI(void* lista);
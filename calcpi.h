#define M_PI 3.14159265358979323846

typedef struct args
{
    long nSerie;
    int nThreads;
    int i;
} valores;

void* calcPI(void* args);
void createAndJoinThreads(int nThreads, valores* v, pthread_t* threads_ids);
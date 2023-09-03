#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<time.h>

int numPrimos;
pthread_mutex_t mutex;

typedef struct {
    long long int ini;
    long long int fim;
} tArgs;

int ehPrimo(long long int n) {
    int i;

    if (n<=1) return 0;
    if (n==2) return 1;
    if (n%2==0) return 0;

    for (i=3; i<sqrt(n)+1; i+=2)
        if(n%i==0) return 0;

    return 1;
}

void *VerificaPrimo(void *args) {
    long long int i, soma_local;
    tArgs arg;

    soma_local = 0;
    arg = *(tArgs *) args;

    for(i = arg.ini; i < arg.fim; i++) {
        if(ehPrimo(i)) soma_local++;
    }
    
    //seção crítica
    pthread_mutex_lock(&mutex);
    numPrimos += soma_local;
    pthread_mutex_unlock(&mutex);

    free(args);

    pthread_exit(NULL);

    return NULL;
}

int main(int argc, char *argv[]) {
    long long int i, N, nthreads;
    clock_t c0, c1;
    double time;
    pthread_t *tid;
    tArgs *args;

    c0 = clock();
    if(c0 == -1) {
        printf("--ERRO: clock()\n");
        return 1;
    }

    numPrimos = 0;

    if(argc<3) {
        printf("Digite: %s <numero de inteiros> <numero de threads>\n", argv[0]);
        return 1;
    }
    N = atoll(argv[1]);
    nthreads = atoll(argv[2]);


    tid = malloc(sizeof(pthread_t) * nthreads);
    if(tid == NULL) {
        printf("--ERRO: malloc()\n");
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < nthreads; i++) {
        args = malloc(sizeof(tArgs));
        if(args == NULL) {
            printf("--ERRO: malloc()\n");
            return 1;
        }

        args->ini = (N * i) / nthreads;
        args->fim = (N * (i + 1)) / nthreads;

        if(pthread_create(&tid[i], NULL, VerificaPrimo, (void *) args)) {
            printf("--ERRO: pthread_create()\n"); exit(-1);
            return 1;
        }
    }

    for (i=0; i<nthreads; i++) {
        if (pthread_join(tid[i], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1);
            return 1;
        } 
    }

    pthread_mutex_destroy(&mutex);

    c1 = clock();
    if(c1 == -1) {
        printf("--ERRO: clock()\n");
        return 1;
    }
    else {
        time = (double) (c1 - c0) / CLOCKS_PER_SEC;
        printf("Com %I64d threads e %I64d numeros: %.10lfs\n", nthreads, N, time);
    }

    // printf("Quantidade de primos = %d\n", numPrimos);

    free(tid);

    return 0;
}
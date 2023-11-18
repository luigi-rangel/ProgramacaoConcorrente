#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int contador = 0;
int nthreads;
pthread_mutex_t mutex;
pthread_cond_t cond_bar;

void barreira(int nthreads) {
    pthread_mutex_lock(&mutex);
    contador++;

    if (contador < nthreads) {
        pthread_cond_wait(&cond_bar, &mutex);
    } else {
        contador=0;
        pthread_cond_broadcast(&cond_bar);
        printf("\n");
    }

    pthread_mutex_unlock(&mutex);
}

void *NThreadsSeCumprimentamNoCorredor(void *targs) {
    long int tid = (long int) targs;

    printf("Ola da thread %ld\n", tid);

    barreira(nthreads);

    printf("Que dia bonito %ld\n", tid);

    barreira(nthreads);

    printf("Ate breve da thread %ld\n", tid);

    pthread_exit(NULL);

    return NULL;
}

int main(int argc, char** argv) {
    int i;
    long int id;
    pthread_t *threads;

    nthreads = atoi(argv[1]);

    threads = malloc(sizeof(pthread_t) * nthreads);

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init (&cond_bar, NULL);

    id = 0;

    for(i = 0; i < nthreads; i++) {
        id++;
        pthread_create(&threads[i], NULL, NThreadsSeCumprimentamNoCorredor, (void *) id);
    }

    for (i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <time.h>

#define NTHREADS 8
#define V_SIZE 10000

typedef struct {
  int *v;
  int start, end;
} arrayInterval;

void *multiplicaVetor (void *arg) {
  arrayInterval arr = *(arrayInterval *) arg;

  for(int i = arr.start; i < arr.end; i++) {
    arr.v[i] *= arr.v[i];
  }

  free(arg);

  pthread_exit(NULL);

  //necessário na versão Windows
  return NULL;
}

int main() {
  int i;
  pthread_t tid_sistema[NTHREADS];
  arrayInterval *args;

  int *v = malloc(sizeof(int) * V_SIZE);
  int *sol = malloc(sizeof(int) * V_SIZE);

  srand(time(NULL));

  for(i = 0; i < V_SIZE; i++) {
    v[i] = rand() % 100;
    sol[i] = v[i] * v[i];
  }


  for(i = 0; i < NTHREADS; i++) {
    args = malloc(sizeof(arrayInterval));
    if (args == NULL) {
      printf("--ERRO: malloc()\n"); exit(-1);
    }

    args->v = v; 
    args->start = (V_SIZE * i) / NTHREADS;
    args->end = (V_SIZE  * (i + 1))/ NTHREADS;
    
    if (pthread_create(&tid_sistema[i], NULL, multiplicaVetor, (void*) args)) {
      printf("--ERRO na criacao da thread %d: pthread_create()\n", i); exit(-1);
    }
  }

  for (i = 0; i < NTHREADS; i++) {
    if (pthread_join(tid_sistema[i], NULL)) {
         printf("--ERROno join da thread %d: pthread_join() \n", i); exit(-1); 
    } 
  }

  for (i = 0; i < V_SIZE; i++) {
    if(v[i] != sol[i]) {
      printf("Erro na posicao %d: %d != %d\n", i, v[i], sol[i]);
      break;
    }
  } if(i == V_SIZE) printf("Todas as operacoes obtiveram sucesso!\n");

  free(v);
  free(sol);

  pthread_exit(NULL);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define N_LINHAS 100 // numero de caracteres por linha
#define B_SIZE 10

// Variaveis globais
sem_t slotCheio, slotVazio; // semaforos para sincronizacao por condicao
sem_t mutexGeral;           // semaforo geral de sincronizacao por exclusao mutua

char Buffer[B_SIZE][100]; // buffer compartilhado

// funcao para retirar um elemento no buffer
char *Retira(void)
{
    char *item;
    static int out = 0;

    item = malloc(N_LINHAS * sizeof(char));

    sem_wait(&slotCheio);  // aguarda slot cheio para retirar
    sem_wait(&mutexGeral); // exclusao mutua entre consumidores

    strncpy(item, Buffer[out], N_LINHAS); // cópia do buffer

    printf("%s\n", item); // impressão ordenada

    out = (out + 1) % B_SIZE; // prosseguimento na fila

    sem_post(&mutexGeral); // libera outras threads
    sem_post(&slotVazio);  // sinaliza um slot vazio

    return item;
}

//----------------------------------------------------------
// Consumidor
void *consumidor(void *arg)
{
    char *item;

    while (true)
    {
        item = Retira(); // retira o proximo item

        free(item); // liberando ponteiro que será sobrescrito na iteração seguinte
    }

    pthread_exit(NULL);

    return NULL;
}

int main(int argc, char **argv)
{
    // declarando variáveis
    int i, nthreads;
    char *fileName, *line;
    bool eof;
    pthread_t *tid;
    FILE *fp;

    eof = false; // inicializando variavel de verificação de fim de arquivo como false

    // iniciando os semaforos
    sem_init(&mutexGeral, 0, 1);
    sem_init(&slotCheio, 0, 0);
    sem_init(&slotVazio, 0, N_LINHAS);

    // alocando memória para o nome do arquivo e para o texto
    fileName = malloc(N_LINHAS * sizeof(char));
    line = malloc(N_LINHAS * sizeof(char));

    // verificando se a chamada ao programa foi no formato correto
    if (argc < 3)
    {
        printf("Chamada ao programa incorreta\n exemplo: %s <nthreads> <caminho_arquivo>\n", argv[0]);
        return 1;
    }

    // convertendo os argumentos em variáveis
    nthreads = atoi(argv[1]);
    fileName = argv[2];

    // abrindo o arquivo de nome dado via CLI
    fp = fopen(fileName, "r");

    tid = malloc(sizeof(pthread_t) * nthreads); // alocando espaço para as threads

    for (i = 0; i < nthreads; i++)
    {
        pthread_create(&tid[i], NULL, consumidor, NULL); // criando threads para consumir
    }

    i = 0;
    // inserindo linha a linha no Buffer
    while (true)
    {
        eof = !fgets(line, N_LINHAS, fp); // transferindo texto para a variável line e guardando a negativa do retorno
        line[strcspn(line, "\n")] = 0;    // retirando '\n' da linha

        if (eof) // se o fgets apontar fim de arquivo não coloca no buffer
            break;

        sem_wait(&slotVazio);
        sem_wait(&mutexGeral);

        strncpy(Buffer[i], line, N_LINHAS);
        i = (i + 1) % B_SIZE; // incrementa o índice do próximo elemento a ser inserido

        sem_post(&mutexGeral); // libera outras threads
        sem_post(&slotCheio);  // sinaliza que um slot foi preenchido
    }

    // espera todas as threads acabarem
    for (i = 0; i < nthreads; i++)
    {
        if (pthread_join(tid[i], NULL))
        {
            printf("--ERROno join da thread %d: pthread_join() \n", i);
            exit(-1);
        }
    }

    // fecha arquivos
    fclose(fp);

    // libera ponteiros globais
    free(fileName);
    free(line);
    free(tid);

    // destroi os semaforos
    sem_destroy(&mutexGeral);
    sem_destroy(&slotCheio);
    sem_destroy(&slotVazio);

    // sai da thread principal
    pthread_exit(NULL);

    return 0;
}

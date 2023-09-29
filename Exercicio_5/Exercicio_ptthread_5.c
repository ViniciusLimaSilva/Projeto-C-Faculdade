#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3 // Tamanho das matrizes
#define NUM_THREADS 2 // Número de threads

// Matrizes de entrada e saída
int A[N][N] = {{1, 2, 3}, {4, 5, 6}, {4, 2, 1}};
int B[N][N] = {{4, 5, 1}, {6, 5, 4}, {1, 1, 1}};
int C[N][N];

// Estrutura para armazenar os índices das linhas a serem calculadas por cada thread
typedef struct {
    int start;
    int end;
} ThreadData;

// Função que calcula a multiplicação das matrizes
void *multiplicarMatrizes(void *data) {
    ThreadData *threadData = (ThreadData *)data;
    int i;
    for (i = threadData->start; i < threadData->end; i++) {
    	int j;
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            int k;
            for ( k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    // Divide o trabalho entre as threads
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        threadData[i].start = i * (N / NUM_THREADS);
        threadData[i].end = (i + 1) * (N / NUM_THREADS);
        pthread_create(&threads[i], NULL, multiplicarMatrizes, &threadData[i]);
    }

    // Aguarda as threads terminarem
    int io;
    for (io = 0; io < NUM_THREADS; io++) {
        pthread_join(threads[io], NULL);
    }

    // Imprime o result
    printf("Matriz Resultante (C):\n");
    int ioo;
    for (ioo = 0; ioo < N; ioo++) {
    	int j;
        for ( j = 0; j < N; j++) {
            printf("%d ", C[ioo][j]);
        }
        printf("\n");
    }

    return 0;
}

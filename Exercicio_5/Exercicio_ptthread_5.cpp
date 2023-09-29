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
    
    for (int i = threadData->start; i < threadData->end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
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
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].start = i * (N / NUM_THREADS);
        threadData[i].end = (i + 1) * (N / NUM_THREADS);
        pthread_create(&threads[i], NULL, multiplicarMatrizes, &threadData[i]);
    }

    // Aguarda as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprime o result
    printf("Matriz Resultante (C):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

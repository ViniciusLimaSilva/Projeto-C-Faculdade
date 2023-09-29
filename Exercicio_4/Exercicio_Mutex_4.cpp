#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_ASSENTOS 50

// Recurso criado (os assentos no teatro)
int assentos[NUM_ASSENTOS];

// Mutex para controlar o acesso aos assentos
pthread_mutex_t mutex_assentos;

// Função que simula a reserva de um assento por um cliente
void *reservarAssento(void *cliente_id) {
    int id = *((int *)cliente_id);

    // Simula a seleção de um assento (escolha aleatória)
    int assento;
    pthread_mutex_lock(&mutex_assentos);
    do {
        assento = rand() % NUM_ASSENTOS;
    } while (assentos[assento] == 1);

    // Marca o assento como reservado
    assentos[assento] = 1;
    pthread_mutex_unlock(&mutex_assentos);

    printf("Cliente %d reservou o assento %d.\n", id, assento);

    free(cliente_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t clientes[NUM_ASSENTOS];
    pthread_mutex_init(&mutex_assentos, NULL);

    // Inicializa os assentos como não reservados (0)
    for (int i = 0; i < NUM_ASSENTOS; i++) {
        assentos[i] = 0;
    }

    // Cria threads para os clientes
    for (int i = 0; i < NUM_ASSENTOS; i++) {
        int *cliente_id = (int *)malloc(sizeof(int));
        *cliente_id = i + 1;
        pthread_create(&clientes[i], NULL, reservarAssento, (void *)cliente_id);
    }

    // Aguarda as threads dos clientes terminarem
    for (int i = 0; i < NUM_ASSENTOS; i++) {
        pthread_join(clientes[i], NULL);
    }

    pthread_mutex_destroy(&mutex_assentos);

    printf("Todas as reservas foram concluídas.\n");

    return 0;
}

#include <stdio.h>	
#include <stdlib.h>
#define M 10

// tipo Elemento
typedef struct {
    int valor;
} Elemento;

// tipo n� usado na lista encadeada
typedef struct no {
    Elemento *elemento;
    struct no *proximo;
} No;

// tipo lista com um ponteiro para o primeiro n�
typedef struct {
    No *inicio;
    int tam;
} Lista;

// nossa tabela (vetor de ponteiros para listas)
Lista *tabela[M];

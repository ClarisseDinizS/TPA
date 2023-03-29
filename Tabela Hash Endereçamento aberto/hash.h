#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#include <time.h>

//--------------------- ESTRUTURAS --------------------

// tipo Elemento para pegar os numeros do arquivo
typedef struct {
    int valor;
} Elemento;

// tipo no usado na lista encadeada
typedef struct no {
    Elemento *elemento;
    struct no *proximo;
} No;

// tipo lista com um ponteiro para o primeiro no
typedef struct {
    No *inicio;
    int tam;
} Lista;

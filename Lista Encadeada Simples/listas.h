#include <stdio.h>
#include <stdlib.h>

typedef struct tipoElemento{
	int valor;
	struct tipoElemento *prox;
}TElemento;

typedef struct tipoLista{
	TElemento *inicio;
	TElemento *fim;
	int total;
}TLista;

void inicializaLista(TLista *lista);
void inserirElemento(TLista *list, int numero);
void exibir_lista(TLista *list);
int menu();

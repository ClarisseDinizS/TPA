#include <stdio.h>
#include <stdlib.h>

//Estrutura da arvore
typedef struct tipoNo{
    
	int valor;
    struct tipoNo *esq, *dir;
    
	int altura;
} TNo;

// Chamada das funcoes

int maior(int a, int b);
int altura(TNo **nodo);
int balanceamento(TNo **nodo);

TNo *inicializaArvore(TNo **nodo);
TNo *remover(TNo **nodo, int valor);
TNo *criaNo(int valor);
TNo *rotDir(TNo **nodo);
TNo *rotEsq(TNo **nodo);
TNo *insere(TNo **nodo, int valor);

void inserir(TNo **nodo);
void removerValor(TNo **nodo);
void caminhamento_em_ordem(TNo *nodo);
void caminhamento_pre_ordem(TNo *nodo);
void caminhamento_pos_ordem(TNo *nodo);
void buscarNo(TNo **nodo, int procurado);
void buscaValor(TNo **nodo, int procurado);
void buscar(TNo **nodo);
void menu(TNo **nodo);


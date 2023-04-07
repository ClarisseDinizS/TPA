// CLARISSE DINIZ SILVA

#include <stdio.h>
#include <stdlib.h>

// Estrutura da arvore com o valor de cada no, esquerda e direita
typedef struct tipoNo
{
    int valor;
    struct tipoNo *esq, *dir;
} TNo;

// Cabecalho de todas as funcoes usadas no programa
TNo *inicializaArvore(TNo **nodo);
TNo *criaNo(int valor);
TNo *insere(TNo **nodo, int valorNovo);
TNo *remover(TNo *nodo, int valorNovo);
void inserir(TNo **nodo);
void removerValor(TNo *nodo);
void imprimir_em_ordem(TNo *nodo);
void imprimir_pre_ordem(TNo *nodo);
void imprimir_pos_ordem(TNo *nodo);
void buscaValor(TNo *nodo, int procurado);
void busca(TNo *nodo, int procurado);
void buscar(TNo *nodo);
void menu(TNo **nodo);

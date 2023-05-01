#include <stdio.h>
#include <stdlib.h>

//Estrutura com nome string do tipo char
typedef char string[300];

//Estrutura da Arvore com nome, matricula e lados direito e esquerdo
typedef struct tipoNo{
    
	long long matricula;
    string nome;
    struct tipoNo *esq, *dir;

} TNo;

// Chamada das funcoes usadas no programa
TNo *inicializaArvore(TNo **nodo);
TNo *insere(TNo **nodo, long long matricula, string *nome);
TNo *remover(TNo **nodo, long long matricula);

void inserirNaArvore(TNo **nodo);
void inserir(TNo **nodo);
void removerValor(TNo **nodo);
void caminhamento_em_ordem(TNo *nodo);
void caminhamento_pre_ordem(TNo *nodo);
void caminhamento_pos_ordem(TNo *nodo);
void buscarNo(TNo **nodo, long long procurado);
void buscaValor(TNo **nodo, long long procurado);
void buscar(TNo **nodo);
void salvarRegistros(TNo **nodo, FILE *arquivo);
void salvar(TNo **nodo);
void menu(TNo **nodo);

